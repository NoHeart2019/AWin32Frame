#include "stdafx.h"
#include "GdiTest.h"

using namespace Gdiplus;

VOID Example_FillPie3(HDC hdc)
{
	Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);
	// Create a SolidBrush object.
	SolidBrush blackBrush(Color(255, 0, 0, 0));

	// Define the pie shape.
	int x = 0;
	int y = 0;
	int width = 200;
	int height = 100;
	REAL startAngle = 0.0f;
	REAL sweepAngle = 45.0f;

	// Fill the pie.
	graphics.FillPie(&blackBrush, x, y, width, height, startAngle, sweepAngle);
}

VOID Example_DrawPolygon(HDC hdc)
{
	Graphics graphics(hdc);

	// Create a Pen object.
	Pen blackPen(Color(255, 0, 0, 0), 3);

	// Create an array of Point objects that define the polygon.
	Point point1(100, 100);
	Point point2(200, 130);
	Point point3(150, 200);
	Point point4(50, 200);
	Point point5(0, 130);
	Point points[5] = {point1, point2, point3, point4, point5};
	Point* pPoints = points;

	// Draw the polygon.
	graphics.DrawPolygon(&blackPen, pPoints, 5);
}


VOID Example_DrawEllipse(HDC hdc)
{
	Graphics graphics(hdc);

	// Create a Pen object.
	Pen bluePen(Color(255, 0, 0, 255),5);

	// Create a Rect object that bounds the ellipse.
	Rect ellipseRect(0, 5, 200, 100);

	// Draw the ellipse.
	graphics.DrawEllipse(&bluePen, ellipseRect);
}


VOID Example_DrawCircle(HDC hdc)
{
	Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	// Create a Pen object.
	Pen bluePen(Color(255, 250, 0, 0),5);

	// Create a Rect object that bounds the ellipse.
	Rect ellipseRect(300, 500, 200, 200);

	// Draw the ellipse.
	graphics.DrawEllipse(&bluePen, ellipseRect);
}


VOID Example_DrawArc(HDC hdc)
{
	Graphics graphics(hdc);

	// Set up the arc.
	Pen redPen(Color(255, 255, 0, 0), 3);
	Rect ellipseRect(0, 0, 200, 100);
	REAL startAngle = 0.0f;
	REAL sweepAngle = 90.0f;

	// Draw the arc.
	graphics.DrawArc(&redPen, ellipseRect, startAngle, sweepAngle);
}


VOID Example_DrawArc4(HDC hdc)
{
	Graphics graphics(hdc);

	// Set up the arc.
	Pen redPen(Color(255, 255, 0, 0), 3);
	REAL x = 0;
	REAL y = 0;
	REAL width = 200.0f;
	REAL height = 100.0f;
	REAL startAngle = 0.0f;
	REAL sweepAngle =60.0f;

	// Draw the arc.
	graphics.DrawArc(&redPen, x, y, width, height, startAngle, sweepAngle);
}

VOID Example_DrawArc30(HDC hdc)
{
	Graphics graphics(hdc);
	graphics.SetSmoothingMode(SmoothingModeAntiAlias);

	// Set up the arc.
	Pen redPen(Color(255, 255, 0, 0), 13);
	Rect ellipseRect(300, 3, 200, 200);
	REAL startAngle = 0.0f;
	REAL sweepAngle = 90.0f;

	// Draw the arc.
	graphics.DrawArc(&redPen, ellipseRect, startAngle, sweepAngle);

	startAngle = sweepAngle;
	Pen greenPen(Color(255, 0, 255, 0), 13);
	graphics.DrawArc(&greenPen, ellipseRect, startAngle, sweepAngle);

	startAngle += 90.0f;
	Pen bluePen(Color(255, 0, 0, 255), 13);

	startAngle += 90.0f;
	graphics.DrawArc(&bluePen, ellipseRect, startAngle, sweepAngle);

	WCHAR string[] = L"70%";

	// Initialize arguments.
	Gdiplus::Font myFont(L"Arial", 16);

	REAL FontHeigth = myFont.GetHeight(&graphics);
	// 400 -22 100
	RectF layoutRect(280.0f, 88.0f, 200.0f, 200.0f);


	StringFormat format;
	format.SetAlignment(StringAlignmentCenter);
	SolidBrush blackBrush(Color(255, 0, 0, 0));

	// Draw string.
	graphics.DrawString(
		string,
		3,
		&myFont,
		layoutRect,
		&format,
		&blackBrush);

}



VOID DrawingOpaqueandSemitransparentLines(HDC hdc)
{
	Graphics graphics(hdc);

	Image image(L"C32Png\\ExploreTree.PNG");
	graphics.DrawImage(&image, 600, 0, image.GetWidth(), image.GetHeight());
	Pen opaquePen(Color(255, 0, 0, 255), 70);
	Pen semiTransPen(Color(128, 0, 0, 255), 32);

	graphics.DrawLine(&opaquePen, 600, 0, 880, 0);
	graphics.DrawLine(&semiTransPen, 600, 86, 880, 86);
	graphics.SetCompositingQuality(CompositingQualityGammaCorrected);
	graphics.DrawLine(&semiTransPen, 600, 158, 880, 158);


}

VOID Example_GdiTest(HDC hdc)
{
	Example_FillPie3(hdc);
	Example_DrawPolygon(hdc);
	Example_DrawEllipse(hdc);
	Example_DrawArc30(hdc);
	//Example_DrawArc4(hdc);
	Example_DrawCircle(hdc);

	DrawingOpaqueandSemitransparentLines(hdc);
}

