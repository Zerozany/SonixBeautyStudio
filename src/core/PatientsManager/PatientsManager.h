_Pragma("once");
#include "ClassesManager.h"

class PatientsManager final : public ClassesManager
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
public:
    static PatientsManager* create(QQmlEngine* _qmlEngine = nullptr, QJSEngine* _qJSEngine = nullptr);

    ~PatientsManager() noexcept override = default;

    Q_DISABLE_COPY_MOVE(PatientsManager)

private:
    explicit(true) PatientsManager(QObject* _parent = nullptr);
};
