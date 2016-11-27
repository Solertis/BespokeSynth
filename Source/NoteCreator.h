//
//  NoteCreator.h
//  Bespoke
//
//  Created by Ryan Challinor on 12/28/15.
//
//

#ifndef __Bespoke__NoteCreator__
#define __Bespoke__NoteCreator__

#include "IDrawableModule.h"
#include "INoteSource.h"
#include "ClickButton.h"
#include "TextEntry.h"
#include "Slider.h"
#include "Transport.h"

class NoteCreator : public IDrawableModule, public INoteSource, public IButtonListener, public ITextEntryListener, public IFloatSliderListener, public IAudioPoller
{
public:
   NoteCreator();
   virtual ~NoteCreator();
   static IDrawableModule* Create() { return new NoteCreator(); }
   
   string GetTitleLabel() override { return "note creator"; }
   void CreateUIControls() override;
   
   void SetEnabled(bool enabled) override { mEnabled = enabled; }
   
   void OnTransportAdvanced(float amount) override;
   
   void KeyPressed(int key, bool isRepeat) override;
   
   void CheckboxUpdated(Checkbox* checkbox) override;
   void ButtonClicked(ClickButton* button) override;
   void TextEntryComplete(TextEntry* entry) override;
   void FloatSliderUpdated(FloatSlider* slider, float oldVal) override {}
   
   void LoadLayout(const ofxJSONElement& moduleInfo) override;
   void SetUpFromSaveData() override;
   
protected:
   void TriggerNote();
   
   //IDrawableModule
   void DrawModule() override;
   bool Enabled() const override { return mEnabled; }
   void GetModuleDimensions(int& w, int& h) override { w=110; h=58; }
   
   ClickButton* mTriggerButton;
   TextEntry* mPitchEntry;
   FloatSlider* mVelocitySlider;
   FloatSlider* mDurationSlider;
   Checkbox* mNoteOnCheckbox;
   int mPitch;
   float mVelocity;
   float mDuration;
   double mStartTime;
   bool mNoteOn;
   bool mNoteOnByTrigger;
};

#endif /* defined(__Bespoke__NoteCreator__) */
