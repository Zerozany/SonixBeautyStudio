pragma Singleton
import QtQuick

QtObject {
    signal pushStack(var _stackPage)

    signal replaceStack(var _stackPage)

    signal popStack
}
