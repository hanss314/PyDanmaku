#include <Python.h>
#include <stdbool.h>
#include <math.h>
#include <list>
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include "../include/bullet.h"
#include "../include/renderer.h"
#include "../include/group.h"
#include "../include/player.h"
#include "../include/laser.h"

std::vector<PyObject*> players;

static PyObject* DanmakuGroup_init(PyObject *self, PyObject *args) {
    char* tex; int is_laser = false;
    if (!PyArg_ParseTuple(args, "Os|p", &self, &tex, &is_laser)) return NULL;
    std::string texture(tex);
    std::list<Bullet*> bullet_list;
    Group *group = new Group(bullet_list, texture, is_laser);
    PyObject* capsule = PyCapsule_New(group, "_c_obj", NULL);
    PyObject_SetAttrString(self, "_c_obj", capsule);
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_del(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    std::list<Bullet*> *bullets = &(group->bullet_list);
    
    for (std::list<Bullet*>::iterator b = bullets.begin(); b != bullets.end(); b++){
        delete *b;
    }
    bullets->clear();
    delete group;
    Py_RETURN_NONE;
}

void check_collisions(std::list<Bullet*> bullets){
    for (std::list<Bullet*>::iterator b = bullets.begin(); b != bullets.end(); b++){
        for(std::vector<PyObject*>::iterator it = players.begin(); it != players.end(); ++it) {
            PyObject* capsule = PyObject_GetAttrString(*it, "_c_obj");
            Player *p = (Player*)PyCapsule_GetPointer(capsule, "_c_obj");
            if((*b)->collides(p->x, p->y, p->r)) {
                PyObject *coll_func = PyObject_GetAttrString(*it, "collision");
                PyObject_CallFunctionObjArgs(coll_func, NULL);
            }
        }
    }
}

static PyObject* DanmakuGroup_run(PyObject *self, PyObject *args) {
    PyObject* parent = NULL;
    if (!PyArg_ParseTuple(args, "O|O", &self, &parent)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    if (parent == NULL) {
        group->run(1.0f);
    } else {
        PyObject* parcapsule = PyObject_GetAttrString(parent, "_c_obj");
        Group *pargroup = (Group*)PyCapsule_GetPointer(parcapsule, "_c_obj");
        group->run(1.0f, *pargroup);
    }
    std::list<Bullet*> *bullets = &(group->bullet_list);
    std::list<Bullet*>::iterator b = bullets->begin();
    while (b != bullets->end()){
        if((*b)->run(1.0f, *group)){
            bullets->erase(b++);
        } else {
            b++;
        }
    }
    check_collisions(*bullets);
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_render(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    render_bullets(group);
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_set_position(PyObject *self, PyObject *args) {
    double x=0, y=0;
    if (!PyArg_ParseTuple(args, "Odd", &self, &x, &y)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    group->x = x; group->y = y;
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_set_angle(PyObject *self, PyObject *args) {
    double ang=0;
    if (!PyArg_ParseTuple(args, "Od", &self, &ang)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    group->angle = ang;
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_set_speed(PyObject *self, PyObject *args) {
    double speed=0;
    if (!PyArg_ParseTuple(args, "Od", &speed)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    group->speed = speed;
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_set_acceleration(PyObject *self, PyObject *args) {
    double acc=0;
    if (!PyArg_ParseTuple(args, "Od", &self, &acc)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    group->acceleration = acc;
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_set_angular_momentum(PyObject *self, PyObject *args) {
    double angm=0;
    if (!PyArg_ParseTuple(args, "Od", &self, &angm)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    group->angular_momentum = angm;
    Py_RETURN_NONE;
}

static PyObject* fromBullet(PyObject *type, Bullet b){
    PyObject *argList = Py_BuildValue("iddddddddd",
        b.life, b.x, b.y, b.angle, b.lx, b.la, b.la,
        b.speed, b.acceleration, b.angular_momentum
    );
    PyObject *obj = PyObject_CallObject(type, argList);
    Py_DECREF(argList);
    return obj;
}

void fromPyObj(PyObject *obj, Bullet *b){
    PyObject* var = PyObject_GetAttrString(obj, "x");
    b->x = PyFloat_AS_DOUBLE(var);
    Py_DECREF(var); var = PyObject_GetAttrString(obj, "y");
    b->y = PyFloat_AS_DOUBLE(var);
    Py_DECREF(var); var = PyObject_GetAttrString(obj, "ang");
    b->angle = PyFloat_AS_DOUBLE(var);
    Py_DECREF(var); var = PyObject_GetAttrString(obj, "speed");
    b->speed = PyFloat_AS_DOUBLE(var);
    Py_DECREF(var); var = PyObject_GetAttrString(obj, "acc");
    b->acceleration = PyFloat_AS_DOUBLE(var);
    Py_DECREF(var); var = PyObject_GetAttrString(obj, "angm");
    b->angular_momentum = PyFloat_AS_DOUBLE(var);
    Py_DECREF(var);
}

static PyObject* DanmakuGroup_run_modifier(PyObject *self, PyObject *args) {
    PyObject *modifier;
    PyObject *bullet_type;
    if (!PyArg_ParseTuple(args, "OOO", &self, &bullet_type, &modifier)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    std::list<Bullet*> *bullets = &(group->bullet_list);
    std::list<Bullet*>::iterator b = bullets->begin();
    while (b != bullets->end()){
        PyObject *bullet = fromBullet(bullet_type, **b);
        PyObject *result = PyObject_CallFunctionObjArgs(modifier, bullet, NULL);
        if (result == NULL){
            bullets->erase(b++);
            continue;
        }
        fromPyObj(result, *b);
        Py_DECREF(bullet); Py_DECREF(result);
        b++;
    }
    Py_RETURN_NONE;
}


static PyObject* DanmakuGroup_add(PyObject *self, PyObject *args){
    double x=0.0f;
    double y=0.0f;
    int is_rect=false;
    double height=0.0f, width=0.0f;
    double angle=0.0f, speed=0.0f;
    double acceleration=0.0f, angular_momentum=0.0f;
    if (!PyArg_ParseTuple(
        args, "Oddpdddddd",
        &self, &x, &y, &is_rect, &height, &width,
        &angle, &speed,
        &acceleration, &angular_momentum
    )) {return NULL;}
    if(is_rect && width == 0.0f){
        width = height;
    }
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    std::list<Bullet*> *bullets = &(group->bullet_list);
    Bullet *b = new Bullet(
        x, y, (bool)is_rect,
        width, height, speed, angle,
        acceleration, angular_momentum
    );
    bullets->emplace_front(b);
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_curvy_laser(PyObject *self, PyObject *args){
    double x=0.0f;
    double y=0.0f;
    int is_rect=false;
    double height=0.0f, width=0.0f;
    double angle=0.0f, speed=0.0f;
    double acceleration=0.0f, angular_momentum=0.0f;
    if (!PyArg_ParseTuple(
            args, "Oddpdddddd",
            &self, &x, &y, &is_rect, &height, &width,
            &angle, &speed,
            &acceleration, &angular_momentum
    )) {return NULL;}
    if(is_rect && width == 0.0f){
        width = height;
    }
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    std::list<Bullet*> *bullets = &(group->bullet_list);
    CurvyLaser *b = new CurvyLaser(
            x, y, (bool)is_rect,
            width, height, speed, angle,
            acceleration, angular_momentum
    );
    bullets->emplace_front(b);
    Py_RETURN_NONE;
}

static PyObject* Danmaku_init(PyObject *self, PyObject *args){
    const char* directory;
    if (!PyArg_ParseTuple(args, "s", &directory)) return NULL;
    renderer_init(directory);
    Py_RETURN_NONE;
}

static PyObject* Danmaku_close(PyObject *self, PyObject *args){
    renderer_close();
    Py_RETURN_NONE;
}

static PyObject* Danmaku_render(PyObject *self, PyObject *args){
    renderer_draw();
    Py_RETURN_NONE;
}

static PyObject* Danmaku_get_keys(PyObject *self, PyObject *args){
    int* keys = get_keys();
    if(keys==NULL) {
        return PyErr_Format(PyExc_RuntimeError, "Renderer has not been initialized.");
    }
    PyObject* py_list = PyList_New(INPUT_COUNT);
    for (int i=0; i<INPUT_COUNT; i++){
        PyList_SetItem(py_list, i, PyLong_FromLong((long)keys[i]));
    }
    return py_list;
}

static PyObject* Player_init(PyObject *self, PyObject *args) {
    char* tex;
    double x=0., y=0., radius=0.;
    if (!PyArg_ParseTuple(
            args, "Oddds",
            &self, &x, &y, &radius, &tex
    )) {return NULL;}

    Player* player = new Player(x, y, radius, tex);
    PyObject* capsule = PyCapsule_New(player, "_c_obj", NULL);
    PyObject_SetAttrString(self, "_c_obj", capsule);
    players.push_back(self);
    Py_RETURN_NONE;
}

static PyObject* Player_step(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    Py_RETURN_NONE;
}

static PyObject* Player_collision(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    Py_RETURN_NONE;
}

static PyObject* Player_set_position(PyObject *self, PyObject *args) {
    double x, y;
    if (!PyArg_ParseTuple(args, "Odd", &self, &x, &y)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Player *player = (Player*)PyCapsule_GetPointer(capsule, "_c_obj");
    player->x = x; player->y = y;
    Py_RETURN_NONE;
}

static PyObject* Player_get_position(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Player *player = (Player*)PyCapsule_GetPointer(capsule, "_c_obj");
    PyObject* tuple = PyTuple_New(2);
    PyTuple_SetItem(tuple, 0, PyFloat_FromDouble(player->x));
    PyTuple_SetItem(tuple, 1, PyFloat_FromDouble(player->y));
    return tuple;
}

static PyObject* Player_run(PyObject *self, PyObject *args) {

    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Player *player = (Player*)PyCapsule_GetPointer(capsule, "_c_obj");
    PyObject* step_func = PyObject_GetAttrString(self, "step");
    PyObject_CallFunctionObjArgs(step_func, NULL);
    render_player(player);
    Py_RETURN_NONE;
}

static PyObject* Player_del(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Player *player = (Player*)PyCapsule_GetPointer(capsule, "_c_obj");
    players.erase(std::remove(players.begin(), players.end(), self), players.end());
    delete player;
    Py_RETURN_NONE;
}

static PyMethodDef DanmakuGroupMethods[] =
{
    {"__init__", DanmakuGroup_init, METH_VARARGS, ""},
    {"__del__", DanmakuGroup_del, METH_VARARGS, ""},
    {"_run", DanmakuGroup_run, METH_VARARGS, ""},
    {"_render", DanmakuGroup_render, METH_VARARGS, ""},
    {"_add_bullet", DanmakuGroup_add, METH_VARARGS, ""},
    {"_curvy_laser", DanmakuGroup_curvy_laser, METH_VARARGS, ""},
    {"set_position", DanmakuGroup_set_position, METH_VARARGS, ""},
    {"set_speed", DanmakuGroup_set_speed, METH_VARARGS, ""},
    {"set_angle", DanmakuGroup_set_angle, METH_VARARGS, ""},
    {"set_accel", DanmakuGroup_set_acceleration, METH_VARARGS, ""},
    {"set_angm", DanmakuGroup_set_angular_momentum, METH_VARARGS, ""},
    {"set_position", DanmakuGroup_set_position, METH_VARARGS, ""},
    {"_run_modifier", DanmakuGroup_run_modifier, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL} ,
};

static PyMethodDef PlayerMethods[] =
{
    {"__init__", Player_init, METH_VARARGS, ""},
    {"__del__", Player_del, METH_VARARGS, ""},
    {"step", Player_step, METH_VARARGS, ""},
    {"collision", Player_collision, METH_VARARGS, ""},
    {"set_pos", Player_set_position, METH_VARARGS, ""},
    {"get_pos", Player_get_position, METH_VARARGS, ""},
    {"run", Player_run, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL} ,
};

static PyMethodDef ModuleMethods[] = {
    {"_init", Danmaku_init, METH_VARARGS, ""},
    {"close", Danmaku_close, METH_VARARGS, ""},
    {"render", Danmaku_render, METH_VARARGS, ""},
    {"get_keys", Danmaku_get_keys, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}
};

static struct PyModuleDef danmakumodule = {
    PyModuleDef_HEAD_INIT,
    "_danmaku",   /* name of module */
    NULL, /* module documentation, may be NULL */
    -1,
    ModuleMethods
};

PyObject *createClassObject(const char *name, PyMethodDef methods[])
{
    PyObject *pClassName = PyUnicode_FromString(name);
    PyObject *pClassBases = PyTuple_New(0); // An empty tuple for bases is equivalent to `(object,)`
    PyObject *pClassDic = PyDict_New();

    PyMethodDef *def;
    // add methods to class
    for (def = methods; def->ml_name != NULL; def++)
    {
        PyObject *func = PyCFunction_New(def, NULL);
        PyObject *method = PyInstanceMethod_New(func);
        PyDict_SetItemString(pClassDic, def->ml_name, method);
        Py_DECREF(func);
        Py_DECREF(method);
    }

    // pClass = type(pClassName, pClassBases, pClassDic)
    PyObject *pClass = PyObject_CallFunctionObjArgs((PyObject *)&PyType_Type, pClassName, pClassBases, pClassDic, NULL);

    Py_DECREF(pClassName);
    Py_DECREF(pClassBases);
    Py_DECREF(pClassDic);

    return pClass;
}

PyMODINIT_FUNC PyInit__pydanmaku(void) {
    PyObject *module;
    module = PyModule_Create(&danmakumodule);
    PyObject* danmakuGroup = createClassObject("_DanmakuGroup", DanmakuGroupMethods);
    PyModule_AddObject(module, "_DanmakuGroup", danmakuGroup);
    PyObject* playerClass = createClassObject("Player", PlayerMethods);
    PyModule_AddObject(module, "Player", playerClass);
    return module;
}
