/****************************************************************************
** Meta object code from reading C++ file 'shaderLoader.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../shaderLoader.h"
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'shaderLoader.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSShaderLoaderENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSShaderLoaderENDCLASS = QtMocHelpers::stringData(
    "ShaderLoader",
    "createDefaultShadersVSFS",
    "",
    "createDefaultShadersVSGSFS",
    "createShaderFromTemplate",
    "attachShaders",
    "name",
    "openFilesInTextEditor",
    "switchStatusVS",
    "switchStatusGS",
    "switchStatusFS",
    "switchStatusWireframe",
    "switchStatusShowAxes",
    "switchStatusShowLight",
    "resetCamera",
    "cameraPreset1",
    "cameraPreset2",
    "cameraPreset3",
    "cameraPreset4",
    "cameraPreset5",
    "loadObject",
    "file",
    "changeBackgroundColor",
    "loadTexture0",
    "loadTexture1",
    "loadTexture2",
    "loadTexture3",
    "showTextures",
    "setLightAmbient",
    "setLightDiffuse",
    "setLightSpecular",
    "setLightPositionWorld",
    "setLightPositionEye",
    "resetLightPosition",
    "switchLightRotate",
    "setMaterialAmbient",
    "setMaterialDiffuse",
    "setMaterialSpecular",
    "editUniform",
    "id",
    "uniformMult",
    "up",
    "executeTest",
    "compareTest"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSShaderLoaderENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,  254,    2, 0x0a,    1 /* Public */,
       3,    0,  255,    2, 0x0a,    2 /* Public */,
       4,    0,  256,    2, 0x0a,    3 /* Public */,
       5,    0,  257,    2, 0x0a,    4 /* Public */,
       5,    1,  258,    2, 0x0a,    5 /* Public */,
       7,    0,  261,    2, 0x0a,    7 /* Public */,
       8,    0,  262,    2, 0x0a,    8 /* Public */,
       9,    0,  263,    2, 0x0a,    9 /* Public */,
      10,    0,  264,    2, 0x0a,   10 /* Public */,
      11,    0,  265,    2, 0x0a,   11 /* Public */,
      12,    0,  266,    2, 0x0a,   12 /* Public */,
      13,    0,  267,    2, 0x0a,   13 /* Public */,
      14,    0,  268,    2, 0x0a,   14 /* Public */,
      15,    0,  269,    2, 0x0a,   15 /* Public */,
      16,    0,  270,    2, 0x0a,   16 /* Public */,
      17,    0,  271,    2, 0x0a,   17 /* Public */,
      18,    0,  272,    2, 0x0a,   18 /* Public */,
      19,    0,  273,    2, 0x0a,   19 /* Public */,
      20,    0,  274,    2, 0x0a,   20 /* Public */,
      20,    1,  275,    2, 0x0a,   21 /* Public */,
      22,    0,  278,    2, 0x0a,   23 /* Public */,
      23,    0,  279,    2, 0x0a,   24 /* Public */,
      24,    0,  280,    2, 0x0a,   25 /* Public */,
      25,    0,  281,    2, 0x0a,   26 /* Public */,
      26,    0,  282,    2, 0x0a,   27 /* Public */,
      27,    0,  283,    2, 0x0a,   28 /* Public */,
      28,    0,  284,    2, 0x0a,   29 /* Public */,
      29,    0,  285,    2, 0x0a,   30 /* Public */,
      30,    0,  286,    2, 0x0a,   31 /* Public */,
      31,    0,  287,    2, 0x0a,   32 /* Public */,
      32,    0,  288,    2, 0x0a,   33 /* Public */,
      33,    0,  289,    2, 0x0a,   34 /* Public */,
      34,    0,  290,    2, 0x0a,   35 /* Public */,
      35,    0,  291,    2, 0x0a,   36 /* Public */,
      36,    0,  292,    2, 0x0a,   37 /* Public */,
      37,    0,  293,    2, 0x0a,   38 /* Public */,
      38,    1,  294,    2, 0x0a,   39 /* Public */,
      40,    1,  297,    2, 0x0a,   41 /* Public */,
      42,    0,  300,    2, 0x0a,   43 /* Public */,
      43,    0,  301,    2, 0x0a,   44 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   39,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::QString,
    QMetaType::Void,

       0        // eod
};

Q_CONSTINIT const QMetaObject ShaderLoader::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSShaderLoaderENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSShaderLoaderENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSShaderLoaderENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<ShaderLoader, std::true_type>,
        // method 'createDefaultShadersVSFS'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createDefaultShadersVSGSFS'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createShaderFromTemplate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'attachShaders'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'attachShaders'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'openFilesInTextEditor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'switchStatusVS'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'switchStatusGS'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'switchStatusFS'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'switchStatusWireframe'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'switchStatusShowAxes'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'switchStatusShowLight'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetCamera'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cameraPreset1'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cameraPreset2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cameraPreset3'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cameraPreset4'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'cameraPreset5'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadObject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadObject'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>,
        // method 'changeBackgroundColor'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadTexture0'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadTexture1'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadTexture2'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'loadTexture3'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'showTextures'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLightAmbient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLightDiffuse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLightSpecular'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLightPositionWorld'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setLightPositionEye'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'resetLightPosition'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'switchLightRotate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setMaterialAmbient'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setMaterialDiffuse'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'setMaterialSpecular'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'editUniform'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'uniformMult'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        // method 'executeTest'
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'compareTest'
        QtPrivate::TypeAndForceComplete<void, std::false_type>
    >,
    nullptr
} };

void ShaderLoader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ShaderLoader *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->createDefaultShadersVSFS(); break;
        case 1: _t->createDefaultShadersVSGSFS(); break;
        case 2: _t->createShaderFromTemplate(); break;
        case 3: _t->attachShaders(); break;
        case 4: _t->attachShaders((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 5: _t->openFilesInTextEditor(); break;
        case 6: _t->switchStatusVS(); break;
        case 7: _t->switchStatusGS(); break;
        case 8: _t->switchStatusFS(); break;
        case 9: _t->switchStatusWireframe(); break;
        case 10: _t->switchStatusShowAxes(); break;
        case 11: _t->switchStatusShowLight(); break;
        case 12: _t->resetCamera(); break;
        case 13: _t->cameraPreset1(); break;
        case 14: _t->cameraPreset2(); break;
        case 15: _t->cameraPreset3(); break;
        case 16: _t->cameraPreset4(); break;
        case 17: _t->cameraPreset5(); break;
        case 18: _t->loadObject(); break;
        case 19: _t->loadObject((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 20: _t->changeBackgroundColor(); break;
        case 21: _t->loadTexture0(); break;
        case 22: _t->loadTexture1(); break;
        case 23: _t->loadTexture2(); break;
        case 24: _t->loadTexture3(); break;
        case 25: _t->showTextures(); break;
        case 26: _t->setLightAmbient(); break;
        case 27: _t->setLightDiffuse(); break;
        case 28: _t->setLightSpecular(); break;
        case 29: _t->setLightPositionWorld(); break;
        case 30: _t->setLightPositionEye(); break;
        case 31: _t->resetLightPosition(); break;
        case 32: _t->switchLightRotate(); break;
        case 33: _t->setMaterialAmbient(); break;
        case 34: _t->setMaterialDiffuse(); break;
        case 35: _t->setMaterialSpecular(); break;
        case 36: _t->editUniform((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 37: _t->uniformMult((*reinterpret_cast< std::add_pointer_t<bool>>(_a[1]))); break;
        case 38: { QString _r = _t->executeTest();
            if (_a[0]) *reinterpret_cast< QString*>(_a[0]) = std::move(_r); }  break;
        case 39: _t->compareTest(); break;
        default: ;
        }
    }
}

const QMetaObject *ShaderLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ShaderLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSShaderLoaderENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Plugin"))
        return static_cast< Plugin*>(this);
    if (!strcmp(_clname, "edu.upc.fib.graug.Plugin/1.0"))
        return static_cast< Plugin*>(this);
    return QObject::qt_metacast(_clname);
}

int ShaderLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 40;
    }
    return _id;
}

#ifdef QT_MOC_EXPORT_PLUGIN_V2
static constexpr unsigned char qt_pluginMetaDataV2_ShaderLoader[] = {
    0xbf, 
    // "IID"
    0x02,  0x66,  'P',  'l',  'u',  'g',  'i',  'n', 
    // "className"
    0x03,  0x6c,  'S',  'h',  'a',  'd',  'e',  'r', 
    'L',  'o',  'a',  'd',  'e',  'r', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN_V2(ShaderLoader, ShaderLoader, qt_pluginMetaDataV2_ShaderLoader)
#else
QT_PLUGIN_METADATA_SECTION
Q_CONSTINIT static constexpr unsigned char qt_pluginMetaData_ShaderLoader[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x66,  'P',  'l',  'u',  'g',  'i',  'n', 
    // "className"
    0x03,  0x6c,  'S',  'h',  'a',  'd',  'e',  'r', 
    'L',  'o',  'a',  'd',  'e',  'r', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(ShaderLoader, ShaderLoader)
#endif  // QT_MOC_EXPORT_PLUGIN_V2

QT_WARNING_POP
