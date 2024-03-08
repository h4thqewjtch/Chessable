/****************************************************************************
** Meta object code from reading C++ file 'piece.h'
**
** Created by: The Qt Meta Object Compiler version 68 (Qt 6.5.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../Project/Piece/piece.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#if __has_include(<QtCore/qtmochelpers.h>)
#include <QtCore/qtmochelpers.h>
#else
QT_BEGIN_MOC_NAMESPACE
#endif


#include <memory>

#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'piece.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 68
#error "This file was generated using the moc from 6.5.3. It"
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
struct qt_meta_stringdata_CLASSPieceENDCLASS_t {};
static constexpr auto qt_meta_stringdata_CLASSPieceENDCLASS = QtMocHelpers::stringData(
    "Piece",
    "signal_to_remove_opponent_piece_label",
    "",
    "DraggableLabel*",
    "update_piece_position",
    "update_pawn_position",
    "update_rook_position",
    "update_knight_position",
    "update_bishop_position",
    "update_queen_position",
    "update_king_position",
    "initialize",
    "is_enough",
    "change"
);
#else  // !QT_MOC_HAS_STRING_DATA
struct qt_meta_stringdata_CLASSPieceENDCLASS_t {
    uint offsetsAndSizes[28];
    char stringdata0[6];
    char stringdata1[38];
    char stringdata2[1];
    char stringdata3[16];
    char stringdata4[22];
    char stringdata5[21];
    char stringdata6[21];
    char stringdata7[23];
    char stringdata8[23];
    char stringdata9[22];
    char stringdata10[21];
    char stringdata11[11];
    char stringdata12[10];
    char stringdata13[7];
};
#define QT_MOC_LITERAL(ofs, len) \
    uint(sizeof(qt_meta_stringdata_CLASSPieceENDCLASS_t::offsetsAndSizes) + ofs), len 
Q_CONSTINIT static const qt_meta_stringdata_CLASSPieceENDCLASS_t qt_meta_stringdata_CLASSPieceENDCLASS = {
    {
        QT_MOC_LITERAL(0, 5),  // "Piece"
        QT_MOC_LITERAL(6, 37),  // "signal_to_remove_opponent_pie..."
        QT_MOC_LITERAL(44, 0),  // ""
        QT_MOC_LITERAL(45, 15),  // "DraggableLabel*"
        QT_MOC_LITERAL(61, 21),  // "update_piece_position"
        QT_MOC_LITERAL(83, 20),  // "update_pawn_position"
        QT_MOC_LITERAL(104, 20),  // "update_rook_position"
        QT_MOC_LITERAL(125, 22),  // "update_knight_position"
        QT_MOC_LITERAL(148, 22),  // "update_bishop_position"
        QT_MOC_LITERAL(171, 21),  // "update_queen_position"
        QT_MOC_LITERAL(193, 20),  // "update_king_position"
        QT_MOC_LITERAL(214, 10),  // "initialize"
        QT_MOC_LITERAL(225, 9),  // "is_enough"
        QT_MOC_LITERAL(235, 6)   // "change"
    },
    "Piece",
    "signal_to_remove_opponent_piece_label",
    "",
    "DraggableLabel*",
    "update_piece_position",
    "update_pawn_position",
    "update_rook_position",
    "update_knight_position",
    "update_bishop_position",
    "update_queen_position",
    "update_king_position",
    "initialize",
    "is_enough",
    "change"
};
#undef QT_MOC_LITERAL
#endif // !QT_MOC_HAS_STRING_DATA
} // unnamed namespace

Q_CONSTINIT static const uint qt_meta_data_CLASSPieceENDCLASS[] = {

 // content:
      11,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags, initial metatype offsets
       1,    1,   80,    2, 0x06,    1 /* Public */,

 // slots: name, argc, parameters, tag, flags, initial metatype offsets
       4,    1,   83,    2, 0x08,    3 /* Private */,
       5,    2,   86,    2, 0x08,    5 /* Private */,
       6,    2,   91,    2, 0x08,    8 /* Private */,
       7,    2,   96,    2, 0x08,   11 /* Private */,
       8,    2,  101,    2, 0x08,   14 /* Private */,
       9,    2,  106,    2, 0x08,   17 /* Private */,
      10,    2,  111,    2, 0x08,   20 /* Private */,
      11,    2,  116,    2, 0x08,   23 /* Private */,
      12,    3,  121,    2, 0x08,   26 /* Private */,
      13,    2,  128,    2, 0x08,   30 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QPoint,    2,
    QMetaType::QPoint, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::QPoint, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::QPoint, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::QPoint, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::QPoint, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::QPoint, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,
    QMetaType::Bool, QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Int, QMetaType::Int, QMetaType::Int,    2,    2,

       0        // eod
};

Q_CONSTINIT const QMetaObject Piece::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_CLASSPieceENDCLASS.offsetsAndSizes,
    qt_meta_data_CLASSPieceENDCLASS,
    qt_static_metacall,
    nullptr,
    qt_incomplete_metaTypeArray<qt_meta_stringdata_CLASSPieceENDCLASS_t,
        // Q_OBJECT / Q_GADGET
        QtPrivate::TypeAndForceComplete<Piece, std::true_type>,
        // method 'signal_to_remove_opponent_piece_label'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<DraggableLabel *, std::false_type>,
        // method 'update_piece_position'
        QtPrivate::TypeAndForceComplete<void, std::false_type>,
        QtPrivate::TypeAndForceComplete<const QPoint &, std::false_type>,
        // method 'update_pawn_position'
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'update_rook_position'
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'update_knight_position'
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'update_bishop_position'
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'update_queen_position'
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'update_king_position'
        QtPrivate::TypeAndForceComplete<QPoint, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'initialize'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'is_enough'
        QtPrivate::TypeAndForceComplete<bool, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        // method 'change'
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>,
        QtPrivate::TypeAndForceComplete<int, std::false_type>
    >,
    nullptr
} };

void Piece::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Piece *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->signal_to_remove_opponent_piece_label((*reinterpret_cast< std::add_pointer_t<DraggableLabel*>>(_a[1]))); break;
        case 1: _t->update_piece_position((*reinterpret_cast< std::add_pointer_t<QPoint>>(_a[1]))); break;
        case 2: { QPoint _r = _t->update_pawn_position((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = std::move(_r); }  break;
        case 3: { QPoint _r = _t->update_rook_position((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = std::move(_r); }  break;
        case 4: { QPoint _r = _t->update_knight_position((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = std::move(_r); }  break;
        case 5: { QPoint _r = _t->update_bishop_position((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = std::move(_r); }  break;
        case 6: { QPoint _r = _t->update_queen_position((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = std::move(_r); }  break;
        case 7: { QPoint _r = _t->update_king_position((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< QPoint*>(_a[0]) = std::move(_r); }  break;
        case 8: { int _r = _t->initialize((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 9: { bool _r = _t->is_enough((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: { int _r = _t->change((*reinterpret_cast< std::add_pointer_t<int>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<int>>(_a[2])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType(); break;
            case 0:
                *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType::fromType< DraggableLabel* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Piece::*)(DraggableLabel * );
            if (_t _q_method = &Piece::signal_to_remove_opponent_piece_label; *reinterpret_cast<_t *>(_a[1]) == _q_method) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject *Piece::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Piece::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_CLASSPieceENDCLASS.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int Piece::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void Piece::signal_to_remove_opponent_piece_label(DraggableLabel * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
