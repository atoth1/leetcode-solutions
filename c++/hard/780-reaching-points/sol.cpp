// https://leetcode.com/problems/reaching-points/

class Solution {
public:
    bool reachingPoints(int sx, int sy, int tx, int ty) {
        if (sx > tx || sy > ty) return false;
        while (tx > sx && ty > sy)
        {
            if (tx > ty)
            {
                tx = tx % ty;
            }
            else
            {
                ty = ty % tx;
            }
        }
        
        if ((sx == tx && (ty-sy) % tx == 0) ||
            (sy == ty && (tx-sx) % ty == 0))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};
