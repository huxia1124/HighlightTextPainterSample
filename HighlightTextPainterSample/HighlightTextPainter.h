#pragma once

#include <string>
#include <list>


class HighlightTextPainter
{

public:
	struct ITextSplitter
	{
		virtual void Split(const wchar_t* text, const wchar_t* keywords, std::list<std::pair<size_t, bool>>& startIndice) = 0;
	};

	struct ITextPainter
	{
		virtual void MeasureText(const wchar_t* text, int len, int& cx, int& cy) = 0;
		virtual void DrawText(const wchar_t* text, int len, int x, int y, int w, int h, bool highlight, bool selected) = 0;
	};


	HighlightTextPainter(const wchar_t* text, const wchar_t* keyword);
	HighlightTextPainter(ITextSplitter* splitter, const wchar_t* text, const wchar_t* keyword);
	void Draw(ITextPainter* painter, int x, int y, int w, int h, bool selected);

	// Default splitter implementation
	class DefaultSplitter : public ITextSplitter
	{
	public:
		DefaultSplitter(bool caseSensitive = true) : _caseSensitive(caseSensitive) {}
	public:
		virtual void Split(const wchar_t* text, const wchar_t* keywords, std::list<std::pair<size_t, bool>>& startIndice);
	private:
		bool _caseSensitive;
	};

	// Default painter implementation
	class GDIPainter : public ITextPainter
	{
	public:
		GDIPainter(HDC hDC) : _hdc(hDC)
		{}

		virtual void MeasureText(const wchar_t* text, int len, int& cx, int& cy);
		virtual void DrawText(const wchar_t* text, int len, int x, int y, int w, int h, bool highlight, bool selected);

	protected:
		HDC _hdc;
	};

protected:
	struct TextInfo
	{
		bool highlight;
		int offsetX;
		int offsetY;
		size_t linebreak;
	};

	int GetNumCharsInLine(ITextPainter* painter, const wchar_t* text, int len, int w);
	void FindLineBreaks(ITextPainter* painter, int w, int h);
	void ApplyLineBreaks(ITextPainter* painter, int w, int h);

	std::wstring _text;		// Original text
	std::list<size_t> _lineBreaks;		// Position of line-breaks
	std::list<std::pair<size_t, bool>> _seg;	// Initial segments generated by the splitter
	std::list<std::pair<size_t, TextInfo>> _dynseg;		// Run-time segments, with information for drawing
};

