#include <Python.h>
#include <stdbool.h>
#include <math.h>
#include <list>
#include <string>
#include <iostream>
#include "../include/bullet.h"
#include "../include/renderer.h"
#include "../include/group.h"


static PyObject* DanmakuGroup_init(PyObject *self, PyObject *args) {
    char* tex;
    if (!PyArg_ParseTuple(args, "Os", &self, &tex)) return NULL;
    std::string texture(tex);
    std::list<Bullet> bullet_list;
    Group *group = new Group(bullet_list, texture);
    PyObject* capsule = PyCapsule_New(group, "_c_obj", NULL);
    PyObject_SetAttrString(self, "_c_obj", capsule);
    Py_RETURN_NONE;
}

static PyObject* DanmakuGroup_del(PyObject *self, PyObject *args) {
    if (!PyArg_ParseTuple(args, "O", &self)) return NULL;
    PyObject* capsule = PyObject_GetAttrString(self, "_c_obj");
    Group *group = (Group*)PyCapsule_GetPointer(capsule, "_c_obj");
    std::list<Bullet> *bullets = &(group->bullet_list);
    bullets->clear();
    delete group;
    Py_RETURN_NONE;
}

bool check_collisions(std::list<Bullet> bullets){
    for (std::list<Bullet>::iterator b = bullets.begin(); b != bullets.end(); b++){
        if(b->collides(320.0, 240.0, 1.0)) return true;
    }
    return false;
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
    std::list<Bullet> *bullets = &(group->bullet_list);
    std::list<Bullet>::iterator b = bullets->begin();
    while (b != bullets->end()){
        if((*b).run(1.0f, *group)){
            bullets->erase(b++);
        } else {
            b++;
        }
    }
    // if (check_collisions(bullets)) std::cout << "Collision!" << std::endl;
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
    std::list<Bullet> *bullets = &(group->bullet_list);
    Bullet b(
        x, y, (bool)is_rect,
        width, height, speed, angle,
        acceleration, angular_momentum
    );
    bullets->emplace_front(b);
    Py_RETURN_NONE;
}

static PyObject* Danmaku_init(PyObject *self, PyObject *args){
    renderer_init();
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

static PyMethodDef DanmakuGroupMethods[] =
{
    {"__init__", DanmakuGroup_init, METH_VARARGS, ""},
    {"__del__", DanmakuGroup_del, METH_VARARGS, ""},
    {"_run", DanmakuGroup_run, METH_VARARGS, ""},
    {"_render", DanmakuGroup_render, METH_VARARGS, ""},
    {"_add_bullet", DanmakuGroup_add, METH_VARARGS, ""},
    {"set_position", DanmakuGroup_set_position, METH_VARARGS, ""},
    {"set_speed", DanmakuGroup_set_speed, METH_VARARGS, ""},
    {"set_angle", DanmakuGroup_set_angle, METH_VARARGS, ""},
    {"set_accel", DanmakuGroup_set_acceleration, METH_VARARGS, ""},
    {"set_angm", DanmakuGroup_set_angular_momentum, METH_VARARGS, ""},
    {"set_position", DanmakuGroup_set_position, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL} ,
};

static PyMethodDef ModuleMethods[] = {
    {"init", Danmaku_init, METH_VARARGS, ""},
    {"close", Danmaku_close, METH_VARARGS, ""},
    {"render", Danmaku_render, METH_VARARGS, ""},
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
    return module;
}
