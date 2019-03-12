#include "stdafx.h"
#include "sgt.h"
#include "rct.h"

inline bool rct::valid(void) const// Etat valide
{
    assert( x2-x1 >= -EPSILON );
    assert( y2-y1 >= -EPSILON );
    return true;
}

// Insertion dans un flux de sortie
ostream& operator<<(ostream& s, const rct& rc)
{
    rc.print(s);
    return s;
}

// Renvoie vrai ssi le segment argt est contenu dans le rectangle (y compris
// les bords).
bool rct::contains(const sgt& s) const
{
    assert(valid());
    return contains(s.get_p1()) || contains(s.get_p2());
}

// Génère un point aléatoire contenu dans le rectangle
pt rct::randPt(void) const
{
    assert(valid());
    pt PtRnd( get_x1() + dRand(height()), get_y1() + dRand(width()) );
    assert( contains(PtRnd) );
    return PtRnd;
}

// Génère un segment aléatoire contenu dans le rectangle
sgt rct::randSgt(void) const
{
    assert(valid());
    return sgt( randPt(), randPt() );
}

// Génère un rectangle aléatoire contenu dans le rectangle
rct rct::randRct(void) const
{
    assert(valid());
<<<<<<< HEAD
    sgt rSgt( randSgt() );
    rct rRand(rSgt.get_p1(), rSgt.get_p2());
=======
    rct rRand(randPt(), randPt());
>>>>>>> 2ee020e0d3dd3ee87c307d7435d0b7b58dce81b7
    assert( contains(rRand) );
    return rRand;
}

void rct::print(ostream& s) const
{
    assert(valid());
    s << "RCT[" << get_x1() << ", " << get_x1()
    << "]x[" << get_y2() << ", " <<get_y2() << "]";
}

// Agrandit le rectangle juste assez pour qu'il contienne le rectangle argument
void rct::unionRct(const rct r2)
{
    assert(valid());
    assert( r2.valid() );

    x1 = min(x1, r2.x1);
    x2 = max(x2, r2.x2);
    y1 = min(y1, r2.y1);
    y2 = max(y2, r2.y2);

    assert(valid());
    assert( contains(r2) );
}


// Renvoie la distance du point argument au rectangle (0 si ptRef est conte-
// nu dans le rectangle, sinon sa distance au plus proche côté du rectangle)
double rct::euclide(const pt& ptRef) const
{
    assert( valid() );

    if( contains(ptRef) )
        return 0.0;

    double d1 = ptRef.euclide(bottomLeft(), bottomRight());
    double d2 = ptRef.euclide(bottomRight(), topRight());
    double d3 = ptRef.euclide(topRight(), topLeft());
    double d4 = ptRef.euclide(topLeft(), bottomLeft());

    double d12 = min(d1,d2);
    double d34 = min(d3,d4);
    return min(d12, d34);
}

// Déformation du rectangle : la largeur est augmentée de la valeur de dx et
// la hauteur de dy, mais sans déplacement du centre. Les arguments dx et dy
// peuvent être négatifs mais de valeur absolue inférieure, respectivement, à
// la largueur ou la hauteur du rectangle, sinon une assertion est déclenchée
#define DEBUG_RCT_INFLATE
void rct::inflate(const double dx, const double dy) const
{
    assert(valid());
#ifdef DEBUG_RCT_INFLATE
    pt OldCenter = centerPt();
    double OldWidth = width();
    double OldHeight = height();
#endif

    assert( dx >= -width());
    assert( dy >= -height());
    x1 -= dx/2.0; x2 += dx/2.0; y1 -= dy/2.0 ; y2 += dy/2.0;

    assert(valid());
#ifdef DEBUG_RCT_INFLATE
    assert( centerPt() == OldCenter );
    assert( EPSEQUAL(width(), OldWidth + dx) );
    assert( EPSEQUAL(height(), OldHeight+dy) );
#endif
}

