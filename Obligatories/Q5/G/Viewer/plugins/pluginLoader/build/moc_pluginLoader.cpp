/****************************************************************************
** Meta object code from reading C++ file 'pluginLoader.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.7.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../pluginLoader.h"
#include <QtCore/qmetatype.h>
#include <QtCore/qplugin.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'pluginLoader.h' doesn't include <QObject>."
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
struct qt_meta_stringdata_CLASSPluginLoaderENDCLASS_t {};
constexpr auto qt_meta_stringdata_CLASSPluginLoaderENDCLASS = QtMocHelpers::stringData(
    "PluginLoader",
    "createDefaultPlugin",
    "",
    "createPluginFromTemplate",
    "attachPlugin",
    "name",
    "openFilesInTextEditor",
    "resetCamera",
    "cameraPreset1",
    "cameraPreset2",
    "cameraPreset3",
    "cameraPreset4",
    "cameraPreset5",
    "loadObject",
    "file"
);
#else  // !QT_MOC_HAS_STRINGDATA
#error "qtmochelpers.h not found or too old."
#endif // !QT_MOC_HAS_STRINGDATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSPluginLoaderENDCLASS[] = {

 // content:
      12,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       1,    0,   92,    2, 0x0a,    1 /* Public */,
       3,    0,   93,    2, 0x0a,    2 /* Public */,
       4,    0,   94,    2, 0x0a,    3 /* Public */,
       4,    1,   95,    2, 0x0a,    4 /* Public */,
       6,    0,   98,    2, 0x0a,    6 /* Public */,
       7,    0,   99,    2, 0x0a,    7 /* Public */,
       8,    0,  100,    2, 0x0a,    8 /* Public */,
       9,    0,  101,    2, 0x0a,    9 /* Public */,
      10,    0,  102,    2, 0x0a,   10 /* Public */,
      11,    0,  103,    2, 0x0a,   11 /* Public */,
      12,    0,  104,    2, 0x0a,   12 /* Public */,
      13,    0,  105,    2, 0x0a,   13 /* Public */,
      13,    1,  106,    2, 0x0a,   14 /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   14,

       0        // eod
};

Q_CONSTINIT const QMetaObject PluginLoader::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSPluginLoaderENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSPluginLoaderENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSPluginLoaderENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<PluginLoader, std::true_type>,
        // method 'createDefaultPlugin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'createPluginFromTemplate'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'attachPlugin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        // method 'attachPlugin'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<QString, std::false_type>,
        // method 'openFilesInTextEditor'
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
        QtPrivate::TypeAndForceComplete<const QString &, std::false_type>
    >,
    nullptr
} };

void PluginLoader::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<PluginLoader *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->createDefaultPlugin(); break;
        case 1: _t->createPluginFromTemplate(); break;
        case 2: _t->attachPlugin(); break;
        case 3: _t->attachPlugin((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 4: _t->openFilesInTextEditor(); break;
        case 5: _t->resetCamera(); break;
        case 6: _t->cameraPreset1(); break;
        case 7: _t->cameraPreset2(); break;
        case 8: _t->cameraPreset3(); break;
        case 9: _t->cameraPreset4(); break;
        case 10: _t->cameraPreset5(); break;
        case 11: _t->loadObject(); break;
        case 12: _t->loadObject((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject *PluginLoader::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *PluginLoader::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSPluginLoaderENDCLASS.stringdata0))
        return static_cast<void*>(this);
    if (!strcmp(_clname, "Plugin"))
        return static_cast< Plugin*>(this);
    if (!strcmp(_clname, "edu.upc.fib.graug.Plugin/1.0"))
        return static_cast< Plugin*>(this);
    return QObject::qt_metacast(_clname);
}

int PluginLoader::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 13;
    }
    return _id;
}

#ifdef QT_MOC_EXPORT_PLUGIN_V2
static constexpr unsigned char qt_pluginMetaDataV2_PluginLoader[] = {
    0xbf, 
    // "IID"
    0x02,  0x66,  'P',  'l',  'u',  'g',  'i',  'n', 
    // "className"
    0x03,  0x6c,  'P',  'l',  'u',  'g',  'i',  'n', 
    'L',  'o',  'a',  'd',  'e',  'r', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN_V2(PluginLoader, PluginLoader, qt_pluginMetaDataV2_PluginLoader)
#else
QT_PLUGIN_METADATA_SECTION
Q_CONSTINIT static constexpr unsigned char qt_pluginMetaData_PluginLoader[] = {
    'Q', 'T', 'M', 'E', 'T', 'A', 'D', 'A', 'T', 'A', ' ', '!',
    // metadata version, Qt version, architectural requirements
    0, QT_VERSION_MAJOR, QT_VERSION_MINOR, qPluginArchRequirements(),
    0xbf, 
    // "IID"
    0x02,  0x66,  'P',  'l',  'u',  'g',  'i',  'n', 
    // "className"
    0x03,  0x6c,  'P',  'l',  'u',  'g',  'i',  'n', 
    'L',  'o',  'a',  'd',  'e',  'r', 
    0xff, 
};
QT_MOC_EXPORT_PLUGIN(PluginLoader, PluginLoader)
#endif  // QT_MOC_EXPORT_PLUGIN_V2

QT_WARNING_POP
