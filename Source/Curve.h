//
//  Curve.h
//  Bespoke
//
//  Created by Ryan Challinor on 3/5/16.
//
//

#ifndef __Bespoke__Curve__
#define __Bespoke__Curve__

#include "OpenFrameworksPort.h"
#include "IClickable.h"

class FileStreamOut;
class FileStreamIn;

struct CurvePoint
{
public:
   CurvePoint() {}
   CurvePoint(float time, float value) : mTime(time), mValue(value) {}
   float mTime;
   float mValue;
};

class Curve : public IClickable
{
public:
   Curve();
   void AddPoint(CurvePoint point);
   void AddPointAtEnd(CurvePoint point);  //only use this if you are sure that there are no points already added at an earlier time
   float Evaluate(float time, bool holdEndForLoop = false);
   void Render() override;
   void SetExtents(float start, float end) { mStart = start; mEnd = end; }
   void SetColor(ofColor color) { mColor = color; }
   void GetDimensions(float& width, float& height) override { width = mWidth; height = mHeight; }
   void SetDimensions(float width, float height) { mWidth = width; mHeight = height; }
   void Clear();
   int GetNumPoints() const { return mNumCurvePoints; }
   CurvePoint* GetPoint(int index);
   
   void SaveState(FileStreamOut& out);
   void LoadState(FileStreamIn& in);
   
protected:
   void OnClicked(int x, int y, bool right) override;
   bool MouseMoved(float x, float y) override;
   bool MouseScrolled(int x, int y, float scrollX, float scrollY) override;

private:
   bool IsAtCapacity() { return mNumCurvePoints >= (int)mPoints.size(); }
   int FindIndexForTime(float time);
   array<CurvePoint,5000> mPoints;
   int mNumCurvePoints;
   float mWidth;
   float mHeight;
   float mStart;
   float mEnd;
   ofColor mColor;
   int mLastEvalIndex;
};

#endif /* defined(__Bespoke__Curve__) */
