#pragma once

class Button
{
public:

    float x;
    float y;

    float width;
    float height;

    float font;
    std::string text = "";

    Button(float X, float Y, float W, float H, float fnt, std::string txt) { x=X; y=Y; width=W; height=H; font=fnt; text=txt; }
    
    void SetText(std::string txt) {text = txt;}
    float TextX() { return float( ((x+1) + ((width / 2.0f)) - (float(text.size()) * (4.0f * font))) ); }
    float TextY() { return float( (y+1) + (height / 2.0f) - (4.0f * font) ); }
    bool IsColliding(int X, int Y) { return ((X > x && X < x + width) && (Y > y && Y < y + height)); }

    void Draw(olc::PixelGameEngine* pge, olc::Pixel bback, olc::Pixel bedge, olc::Pixel hedge, olc::Pixel btext)
    {
        bool isColliding = IsColliding(pge->GetMouseX(), pge->GetMouseY());
        pge->FillRectDecal({ x, y }, { width, height }, bback);
        pge->DrawRectDecal(static_cast<int32_t>(x), static_cast<int32_t>(y), static_cast<int32_t>(width), static_cast<int32_t>(height), isColliding? hedge : bedge);

        pge->DrawStringDecal({ TextX(), TextY() }, text, btext, {font, font});
    }
};
