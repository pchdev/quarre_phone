#include "modulemanager.h"
#include <QtDebug>
#include <QCoreApplication>
#include <QDir>

using namespace quarre;

InteractionModuleManager::InteractionModuleManager() :
    r_active_module(nullptr) {

    QString path(QCoreApplication::applicationDirPath());
    QDir dir(path);

    // load each plugin
    foreach(QString file, dir.entryList()) {
        if(file.startsWith("libquarre_plugin")) {
            QPluginLoader loader(file);
            if(!loader.load()) qDebug() << "FAILED TO LOAD QUARRE PLUGIN: " << file;
            else {
                qDebug() << "PLUGIN SUCCESFULLY LOADED: " << file;
                am_interaction_modules << qobject_cast<quarre::InteractionModule*>(loader.instance());
            }
        }
    }
}

InteractionModuleManager::~InteractionModuleManager() {
    foreach(quarre::InteractionModule *module, am_interaction_modules) {
        delete module;}
}

quarre::InteractionModule* InteractionModuleManager::getModuleReferenceByName(QString target) const {
    foreach(quarre::InteractionModule *module, am_interaction_modules) {
        if(module->getModuleIdentifier() == target) return module;
    }
}

QList<quarre::InteractionModule*> InteractionModuleManager::getInteractionModulesReferences() const {
    return am_interaction_modules;
}

void InteractionModuleManager::setActiveModule(InteractionModule *module) {
    r_active_module = module;
}

quarre::InteractionModule* InteractionModuleManager::getActiveModule() const {
    return r_active_module;
}
