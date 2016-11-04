#include "osbridge.h"
#include <QDebug>

using namespace quarre;

OSBridge::OSBridge() :
    m_flash_available(false),
    m_torch_timer(new QTimer(this)) {

    QObject::connect(m_torch_timer, SIGNAL(timeout()), this, SLOT(torchTimerCallback()));

    // NEED TO INTEGRATE ANDROIDJNI ERROR MANAGEMENT!!

    /* ANDROID */

#ifdef Q_OS_ANDROID

    // CATCH TORCHMODE
    QAndroidJniObject camera_string = QAndroidJniObject::fromString("camera");
    QAndroidJniObject camera_activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject camera_app_context = camera_activity.callObjectMethod("getApplicationContext", "()Landroid/content/Context;");
    m_camera_manager = camera_app_context.callObjectMethod("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;", camera_string.object<jstring>());

    // CATCH VIBRATOR DEVICE
    QAndroidJniObject vibr_string = QAndroidJniObject::fromString("vibrator");
    QAndroidJniObject vibr_activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject vibr_app_context = vibr_activity.callObjectMethod("getApplicationContext", "()Landroid/content/Context;");
    m_vibrator = vibr_app_context.callObjectMethod("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;", vibr_string.object<jstring>());

    // CATCH & ACTIVATE WAKELOCK
    QAndroidJniObject wl_activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject service_name = QAndroidJniObject::getStaticObjectField<jstring>("android/content/Context", "POWER_SERVICE");
    QAndroidJniObject power_mgr = wl_activity.callObjectMethod("getSystemService", "(Ljava/lang/String;)Ljava/lang/Object;", service_name.object<jobject>());
    jint level_and_flags = QAndroidJniObject::getStaticField<jint>("android/os/PowerManager", "SCREEN_BRIGHT_WAKE_LOCK");
    QAndroidJniObject tag = QAndroidJniObject::fromString("My Tag");
    m_wake_lock = power_mgr.callObjectMethod("newWakeLock", "(ILjava/lang/String;)Landroid/os/PowerManager$WakeLock;", level_and_flags, tag.object<jstring>());

    if(m_wake_lock.isValid()) {
        m_wake_lock.callMethod<void>("acquire", "()V");
        qDebug() << "Locked device, cannot go to standby anymore";
    } else {
        qDebug() << "Unable to lock device..!!";
    }

#endif

    /* IOS ? */

}

OSBridge::~OSBridge() {
    delete m_torch_timer;
}

#ifdef Q_OS_ANDROID

void OSBridge::vibrate(int milliseconds) const {
    jlong ms = milliseconds;
    jboolean has_vibrator = m_vibrator.callMethod<jboolean>("hasVibrator", "()Z");
    m_vibrator.callMethod<void>("vibrate", "(J)V", ms);
}

void OSBridge::light(int milliseconds) const {
    // note, this only works if back camera is registered as the #0 id, need to check-it first
    QAndroidJniObject back_camera_id = QAndroidJniObject::fromString("0");
    jboolean on = true;
    m_camera_manager.callMethod<void>("setTorchMode", "(Ljava/lang/String;Z)V", back_camera_id.object<jstring>(), on);
    m_torch_timer->start(milliseconds);
}

void OSBridge::torchTimerCallback() {
    QAndroidJniObject back_camera_id = QAndroidJniObject::fromString("0");
    jboolean off = false;
    m_camera_manager.callMethod<void>("setTorchMode", "(Ljava/lang/String;Z)V", back_camera_id.object<jstring>(), off);
    m_torch_timer->stop();
}

#endif
