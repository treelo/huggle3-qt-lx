//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

#include "hooks.hpp"
#include "core.hpp"
#include "mainwindow.hpp"
#include "vandalnw.hpp"
#include "iextension.hpp"
#include "wikiuser.hpp"
#include "wikiedit.hpp"
#include "syslog.hpp"
#include "exception.hpp"
#include "wikipage.hpp"

void Huggle::Hooks::EditPreProcess(Huggle::WikiEdit *Edit)
{
    if (Edit == nullptr)
    {
        throw new Huggle::Exception("Huggle::WikiEdit *Edit must not be nullptr", "void Huggle::Hooks::EditPreProcess(Huggle::WikiEdit *Edit)");
    }
    int extension = 0;
    while (extension < Huggle::Core::HuggleCore->Extensions.count())
    {
        Huggle::iExtension *e = Huggle::Core::HuggleCore->Extensions.at(extension);
        if (e->IsWorking())
        {
            e->Hook_EditPreProcess((void*)Edit);
        }
        extension++;
    }
}

void Huggle::Hooks::EditPostProcess(Huggle::WikiEdit *Edit)
{
    if (Edit == nullptr)
    {
        throw new Exception("Huggle::WikiEdit *Edit must not be nullptr", "void Huggle::Hooks::EditPreProcess(Huggle::WikiEdit *Edit)");
    }
    int extension = 0;
    while (extension < Huggle::Core::HuggleCore->Extensions.count())
    {
        Huggle::iExtension *e = Huggle::Core::HuggleCore->Extensions.at(extension);
        if (e->IsWorking())
        {
            e->Hook_EditPostProcess((void*)Edit);
        }
        extension++;
    }
}

void Huggle::Hooks::OnGood(Huggle::WikiEdit *Edit)
{
    Core::HuggleCore->Main->VandalDock->Good(Edit);
}

void Huggle::Hooks::OnRevert(Huggle::WikiEdit *Edit)
{
    Core::HuggleCore->Main->VandalDock->Rollback(Edit);
}

void Huggle::Hooks::OnWarning(Huggle::WikiUser *User)
{
    Core::HuggleCore->Main->VandalDock->WarningSent(User, User->WarningLevel);
}

void Huggle::Hooks::Suspicious(Huggle::WikiEdit *Edit)
{
    Core::HuggleCore->Main->VandalDock->SuspiciousWikiEdit(Edit);
}

void Huggle::Hooks::BadnessScore(Huggle::WikiUser *User, int Score)
{
    if (User == nullptr)
    {
        throw new Exception("Huggle::WikiUser *User must not be nullptr", "void Huggle::Hooks::BadnessScore(Huggle::WikiUser "\
                            "*User, int Score)");
    }
    int extension = 0;
    while (extension < Huggle::Core::HuggleCore->Extensions.count())
    {
        Huggle::iExtension *e = Huggle::Core::HuggleCore->Extensions.at(extension);
        if (e->IsWorking())
        {
            e->Hook_BadnessScore((void*)User, Score);
        }
        extension++;
    }
}

void Huggle::Hooks::Speedy_Finished(Huggle::WikiEdit *edit, QString tags, bool success)
{
    foreach (Huggle::iExtension *e, Huggle::Core::HuggleCore->Extensions)
    {
        if (e->IsWorking())
            e->Hook_SpeedyFinished((void*)edit, tags, success);
    }
#ifdef PYTHONENGINE
    Huggle::Core::HuggleCore->Python->Hook_SpeedyFinished(edit, tags, success);
#endif
}

void Huggle::Hooks::MainWindowIsLoaded(Huggle::MainWindow *window)
{
    foreach (Huggle::iExtension *e, Huggle::Core::HuggleCore->Extensions)
    {
        if (e->IsWorking())
            e->Hook_MainWindowOnLoad((void*)window);
    }
#ifdef PYTHONENGINE
    Huggle::Core::HuggleCore->Python->Hook_MainWindowIsLoaded();
#endif
}

void Huggle::Hooks::Shutdown()
{
    foreach (Huggle::iExtension *e, Huggle::Core::HuggleCore->Extensions)
    {
        if ( e->IsWorking() )
           e->Hook_Shutdown();
    }
#ifdef PYTHONENGINE
    Huggle::Core::HuggleCore->Python->Hook_HuggleShutdown();
#endif
}
