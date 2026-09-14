_Pragma("once");

#define QUICK_PROPERTY(_valueType, _memberName, _valueName, _readValueName, _setValueName, _notifyName) \
    Q_PROPERTY(_valueType _valueName READ _readValueName WRITE _setValueName NOTIFY _notifyName)        \
public:                                                                                                 \
    _valueType _readValueName() const { return _memberName; }                                           \
    void       _setValueName(const _valueType& _##_valueName)                                           \
    {                                                                                                   \
        if (_memberName == _##_valueName)                                                               \
        {                                                                                               \
            return;                                                                                     \
        }                                                                                               \
        _memberName = _##_valueName;                                                                    \
        Q_EMIT this->_notifyName();                                                                     \
    }
