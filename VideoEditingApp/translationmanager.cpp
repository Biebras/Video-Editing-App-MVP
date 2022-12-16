#include "translationmanager.h"

void TranslationManager::InitTranslation(QTranslator& translator)
{
    _translator = &translator;

    SetLanguage("en");
}

void TranslationManager::SetLanguage(QString language)
{
    _translator->load(":languages/translation_" + language + ".qm");
    qApp->installTranslator(_translator);
    _sceneManager.RetranslateScenes();
}
