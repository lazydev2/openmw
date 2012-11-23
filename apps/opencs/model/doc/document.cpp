
#include "document.hpp"

CSMDoc::Document::Document()
{
    connect (&mUndoStack, SIGNAL (cleanChanged (bool)), this, SLOT (modificationStateChanged (bool)));

     // dummy implementation -> remove when proper save is implemented.
    mSaveCount = 0;
    connect (&mSaveTimer, SIGNAL(timeout()), this, SLOT (saving()));
}

QUndoStack& CSMDoc::Document::getUndoStack()
{
    return mUndoStack;
}

int CSMDoc::Document::getState() const
{
    int state = 0;

    if (!mUndoStack.isClean())
        state |= State_Modified;

    if (mSaveCount)
        state |= State_Locked | State_Saving | State_Progress;

    return state;
}

void CSMDoc::Document::save()
{
    mSaveCount = 1;
    mSaveTimer.start (500);
    emit stateChanged (getState(), this);
    emit progress (1, 16, this);
}

void CSMDoc::Document::abortSave()
{
    mSaveTimer.stop();
    emit stateChanged (getState(), this);
}

void CSMDoc::Document::modificationStateChanged (bool clean)
{
    emit stateChanged (getState(), this);
}

void CSMDoc::Document::saving()
{
    ++mSaveCount;

    emit progress (mSaveCount, 16, this);

    if (mSaveCount>15)
    {
            mSaveCount = 0;
            mSaveTimer.stop();
            mUndoStack.setClean();
            emit stateChanged (getState(), this);
    }
}