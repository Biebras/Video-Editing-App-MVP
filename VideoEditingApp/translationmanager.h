#ifndef TRANSLATIONMANAGER_H
#define TRANSLATIONMANAGER_H

#include <QApplication>
#include <QtWidgets>

class TranslationManager
{
    public:
        TranslationManager(const TranslationManager&) = delete;

        static TranslationManager& Get()
        {
            static TranslationManager instance;
            return instance;
        };

        void InitTranslations();
        void SetLanguage(QString language, QApplication& app);

    private:
        TranslationManager(){};
        QTranslator* _translator;
};

#endif // TRANSLATIONMANAGER_H
