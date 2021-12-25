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
    float TextX() { return float( ((x+1) + ((width/2.0)) - (float(text.size())*(4.0*font))) ); }
    float TextY() { return float( (y+1) + (height/2.0) - (4.0*font) ); }
    bool IsColliding(int X, int Y) { return ((X > x && X < x+width) && (Y > y && Y < y+height)); }

    void Draw(olc::PixelGameEngine* pge, olc::Pixel bback, olc::Pixel bedge, olc::Pixel hedge, olc::Pixel btext)
    {
        pge->DrawStringDecal({ TextX(),TextY() }, text, btext, {font, font});
        pge->FillRect(x, y, width, height, bback);
        if (IsColliding(pge->GetMouseX(), pge->GetMouseY())) { pge->DrawRect(x, y, width, height, hedge); return; }
        pge->DrawRect(x, y, width, height, bedge);
    }
};
