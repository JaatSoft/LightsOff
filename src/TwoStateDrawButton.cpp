#include "TwoStateDrawButton.h"


TwoStateDrawButton::TwoStateDrawButton(BRect frame, const char *name,
	BBitmap *upone, BBitmap *downone, BBitmap *uptwo, BBitmap *downtwo,
	BMessage *msg)
	:
	BButton(frame, name, "", msg, B_FOLLOW_NONE, B_WILL_DRAW),
 	fUpOne(upone),
	fDownOne(downone),
	fUpTwo(uptwo),
	fDownTwo(downtwo),
	fDisabledOne(NULL),
	fDisabledTwo(NULL),
	fButtonState(false)
{
}


TwoStateDrawButton::~TwoStateDrawButton()
{
	delete fUpOne;
	delete fDownOne;
	delete fUpTwo;
	delete fDownTwo;
	delete fDisabledOne;
	delete fDisabledTwo;
}


void
TwoStateDrawButton::ResizeToPreferred(void)
{
	if(fUpOne)
		ResizeTo(fUpOne->Bounds().Width(),fUpOne->Bounds().Height());
	else
	if(fDownOne)
		ResizeTo(fDownOne->Bounds().Width(),fDownOne->Bounds().Height());
	else
	if(fUpTwo)
		ResizeTo(fUpTwo->Bounds().Width(),fUpTwo->Bounds().Height());
	else
	if(fDownTwo)
		ResizeTo(fDownTwo->Bounds().Width(),fDownTwo->Bounds().Height());
	else
	if(fDisabledOne)
		ResizeTo(fDisabledOne->Bounds().Width(),fDisabledOne->Bounds().Height());
	else
	if(fDisabledTwo)
		ResizeTo(fDisabledTwo->Bounds().Width(),fDisabledTwo->Bounds().Height());
}

void
TwoStateDrawButton::SetBitmaps(BBitmap *upone, BBitmap *downone, BBitmap *uptwo, 
									BBitmap *downtwo)
{	
	delete fUpOne;
	delete fDownOne;
	delete fUpTwo;
	delete fDownTwo;
	
	fUpOne = upone;
	fDownOne = downone;
	fUpTwo = uptwo;
	fDownTwo = downtwo;
}


void TwoStateDrawButton::SetDisabled(BBitmap *disabledone, BBitmap *disabledtwo)
{
	delete fDisabledOne;
	delete fDisabledTwo;

	fDisabledOne = disabledone;
	fDisabledTwo = disabledtwo;
}


void TwoStateDrawButton::MouseUp(BPoint pt)
{
	BButton::MouseUp(pt);
	Invalidate();
}


void
TwoStateDrawButton::SetState(int32 value)
{
	bool state = value != 0;

	if (fButtonState != state) {
		fButtonState = state;
		Invalidate();
	}
}


void TwoStateDrawButton::Draw(BRect update)
{
	if(fButtonState)
	{
		if(!IsEnabled())
		{
			if(fDisabledTwo)
				DrawBitmap(fDisabledTwo, BPoint(0,0));
			else
				StrokeRect(Bounds());
			return;
		}
		
		if(Value() == B_CONTROL_ON)
		{
			if(fDownTwo)
				DrawBitmap(fDownTwo, BPoint(0,0));
			else
				StrokeRect(Bounds());
		}
		else
		{
			if(fUpTwo)
				DrawBitmap(fUpTwo, BPoint(0,0));
			else
				StrokeRect(Bounds());
		}
	}
	else
	{
		if(!IsEnabled())
		{
			if(fDisabledOne)
				DrawBitmap(fDisabledOne, BPoint(0,0));
			else
				StrokeRect(Bounds());
			return;
		}
		
		if(Value() == B_CONTROL_ON)
		{
			if(fDownOne)
				DrawBitmap(fDownOne, BPoint(0,0));
			else
				StrokeRect(Bounds());
		}
		else
		{
			if(fUpOne)
				DrawBitmap(fUpOne, BPoint(0,0));
			else
				StrokeRect(Bounds());
		}
	}
}

