#ifndef ANIMATEDTILE
#define ANIMATEDTILE

#include "tile.h"
#include "globals.h"

#include <vector>

class AnimatedTile : public Tile{
    public:
        AnimatedTile(std::vector<Vector2f> p_tilesetPositions, int p_duration, 
            SDL_Texture* p_tileset, Vector2f p_size, Vector2f p_position);
        void update(int p_elapsedTime);
        void draw(Graphics &p_graphics);
    protected:
        int _amountOfTime = 0;
        bool _notDone = false;
    private:
        std::vector<Vector2f> _tilesetPositions;
        int _tileToDraw;
        int _duration;
};

struct AnimatedTileInfo{
    public:
        int TilesetsFirstGid;
        int StartTileId;
        std::vector<int> TileIds;
        int Duration;
};

#endif /* ANIMATEDTILE */
