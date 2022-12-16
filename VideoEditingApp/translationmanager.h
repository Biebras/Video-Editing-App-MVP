#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H

#include <QTranslator>
#include <QApplication>
#include <QDebug>
#include "scenemanager.h"

class TranslationManager
{
    public:
        TranslationManager(const TranslationManager&) = delete;

        //singleton
        static TranslationManager& Get()
        {
            static TranslationManager instance;
            return instance;
        };

        void InitTranslation(QTranslator& translator);
        void SetLanguage(QString language);

    private:
        TranslationManager(){}
        QTranslator* _translator;
        SceneManager& _sceneManager = SceneManager::Get();
};

#endif // TRANSLATIONMANAGER_H
