/****************************************************************************
** Meta object code from reading C++ file 'glwidget.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../include/glwidget.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'glwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.7.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {

#ifdef QT_MOC_HAS_STRINGDATA
struct qt_meta_stringdata_CLASSGLWidgetENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSGLWidgetENDCLASS = QtMocHelpers::stringData(
    "GLWidget",
    "addObject",
    "",
    "addObjectFromFile",
    "filename",
    "clearScene",
    "resetCamera",
    "drawAxes",
    "drawPoint",
    "Vector",
    "pos",
    "r",
    "g",
    "b",
    "boundingBoxIncludingAxes",
    "Box",
    "loadPlugin",
    "loadPlugins",
    "list",
    "loadDefaultPlugins",
    "QString&",
    "plugins",
    "resetPluginsToDefaults",
    "unloadPlugin",
    "i"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSGLWidgetENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   86,    2, 0x0a,    1 /* Public */,
       3,    1,   87,    2, 0x0a,    2 /* Public */,
       5,    0,   90,    2, 0x0a,    4 /* Public */,
       6,    0,   91,    2, 0x0a,    5 /* Public */,
       7,    0,   92,    2, 0x0a,    6 /* Public */,
       8,    4,   93,    2, 0x0a,    7 /* Public */,
      14,    0,  102,    2, 0x0a,   12 /* Public */,
      16,    0,  103,    2, 0x0a,   13 /* Public */,
      17,    1,  104,    2, 0x0a,   14 /* Public */,
      19,    1,  107,    2, 0x0a,   16 /* Public */,
      22,    0,  110,    2, 0x0a,   18 /* Public */,
      23,    1,  111,    2, 0x0a,   19 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Float, QMetaType::Float, QMetaType::Float,   10,   11,   12,   13,
    0x80000000 | 15,
    QMetaType::Void,
    QMetaType::Int, QMetaType::QStringList,   18,
    QMetaType::Void, 0x80000000 | 20,   21,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   24,

       0        // eod
};

Q_CONSTINIT const QMetaObject GLWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QOpenGLWidget::staticMetaObject>(),
    qt_meta_stringdata_CLASSGLWidgetENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSGLWidgetENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSGLWidgetENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<GLWidget, std::true_type>,
        // method 'addObject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'addObjectFromFile'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'clearScene'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetCamera'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'drawAxes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'drawPoint'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const Vector &, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        QtPrivate::TypeAndForceComplete<float, std::false_type>,
        // method 'boundingBoxIncludingAxes'
        QtPrivate::TypeAndForceComplete<Box, std::false_type>,
        // method 'loadPlugin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadPlugins'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QStringList &, std::false_type>,
        // method 'loadDefaultPlugins'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString &, std::false_type>,
        // method 'resetPluginsToDefaults'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'unloadPlugin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void GLWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<GLWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->addObject(); break;
        case 1: _t->addObjectFromFile((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 2: _t->clearScene(); break;
        case 3: _t->resetCamera(); break;
        case 4: _t->drawAxes(); break;
        case 5: _t->drawPoint((*reinterpret_cast< std::add_pointer_t<Vector>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[4]))); break;
        case 6: { Box _r = _t->boundingBoxIncludingAxes();
            if (_a[0]) *reinterpret_cast< Box*>(_a[0]) = std::move(_r); }  break;
        case 7: _t->loadPlugin(); break;
        case 8: { int _r = _t->loadPlugins((*reinterpret_cast< std::add_pointer_t<QStringList>>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: _t->loadDefaultPlugins((*reinterpret_cast< std::add_pointer_t<QString&>>(_a[1]))); break;
        case 10: _t->resetPluginsToDefaults(); break;
        case 11: _t->unloadPlugin((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *GLWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GLWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSGLWidgetENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "QOpenGLFunctions_3_3_Core"))
        return static_cast< QOpenGLFunctions_3_3_Core*>(this);
    return QOpenGLWidget::qt_metacast(_clname);
}

int GLWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QOpenGLWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
