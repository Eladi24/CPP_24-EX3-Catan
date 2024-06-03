#ifndef _CATAN_HPP_
#define _CATAN_HPP_

namespace ariel
{
    class Catan
    {
    private:
        Player _p1;
        Player _p2;
        Player _p3;
        Board _board;
        vector<ResourceType> _pack1;
        vector<ResourceType> _pack2;
        vector<ResourceType> _pack3;
        vector<ResourceType> _pack4;
        vector<ResourceType> _pack5;
        map<DevCard, int> _devCardsPack; 
    public:
        Catan(Player p1, Player p2, Player p3);
        ~Catan();
        void ChooseStartingPlayer();
        Board getBoard();
        void printWinner();
    };
} // namespace ariel


#endif