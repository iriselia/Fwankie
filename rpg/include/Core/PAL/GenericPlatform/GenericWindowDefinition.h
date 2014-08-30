#pragma once

#include "Core.h"

struct GenericWindowDefinition
{
	float XDesiredPositionOnScreen;
	float YDesiredPositionOnScreen;

	float WidthDesiredOnScreen;
	float HeightDesiredOnScreen;

	bool HasOSWindowBorder;
	bool SupportsTransparency;
	bool AppearsInTaskbar;
	bool IsTopmostWindow;
	bool AcceptsInput;
	bool ActivateWhenFirstShown;

	bool SupportsMinimize;
	bool SupportsMaximize;

	bool IsRegularWindow;
	bool HasSizingFrame;
	bool SizeWillChangeOften;
	int32 ExpectedMaxWidth;
	int32 ExpectedMaxHeight;

	std::tstring Title;
	float Opacity;
	int32 CornerRadius;
};