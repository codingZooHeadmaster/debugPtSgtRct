#pragma once
#include "./pt.h"
class pt;
class sgt;

class rct
{
private:
    // Data _________________________________________________________________________

    // Un rectangle parallèle aux axes est défini par les abscisses de ses cotés
    // gauche (x1) & droit (x2) et les ordonnées des cotés haut (y2) & bas (y1).

    double x1, x2, y1, y2; // x1 <= x2 et y1 <= y2

    // Un rectangle peut être dégénéré : en un point, quand sa largeur et sa hau-
    // teur sont nulles), ou en un segment, quand sa largeur est nulle ou bien sa
    // hauteur est nulle), ou dégénéré , mais il n'est jamais vide au sens ensem-
    // bliste. Ce qu'il faut prendre en considération pour les calculs d'union et
    // d'intersection de deux rectangles).

public:
    // Mise au point ________________________________________________________________

    // Cette fonction renvoie *toujours* vrai, mais en configuration DEBUG, elle
    // déclenche auparavant une assertion si la condition (x1 <= x2 et y1 <= y2)
    // n'est pas vraie.
    bool valid(void) const;


    // Construction _________________________________________________________________

    // Construction par défaut : rectangle réduit à un seul point (0,0)
    rct(void);

    // Construction à partir des bords [x1..x2]x[y1..y2]
    rct(const double x1_, const double x2_, const double y1_, const double y2_);

    // Construction à partir de deux points absolument quelconques : le plus pe-
    // tit rectangle qui contient les deux points.
    rct(const pt p1, const pt p2);

    // L'opérateur d'affectation implicite et le constructeur de copie implicite
    // conviennent. On ne les code pas explicitement.
    //rct(const rct& r2);

    // Attributs ___________________________________________________________________

    double get_x1(void) const;	            // Renvoie l'abscisse du coté gauche
    double get_x2(void) const;               // Renvoie l'abscisse du coté droit
    double get_y1(void) const;	               // Renvoie l'ordonnée du coté bas
    double get_y2(void) const;                // Renvoie l'ordonnée du coté haut


    pt bottomLeft(void) const;               // Renvoie le coin inférieur gauche
    pt topRight(void) const;                  // Renvoie le coin supérieur droit
    pt topLeft(void) const;                  // Renvoie le coin supérieur gauche
    pt bottomRight(void) const;               // Renvoie le coin inférieur droit
    pt centerPt(void) const;                         // Renvoie le point central

    double width(void) const;                              // Renvoie la largeur
    double height(void) const;                             // Renvoie la hauteur
    double area(void) const;                               // Renvoie la surface

    // Prédicats ___________________________________________________________________

    // Deux rectangles sont égaux s'ils ont les mêmes limites
    bool operator==(const rct& s2) const;

    // Renvoie vrai ssi le point argument est contenu dans le rectangle
    bool contains(const pt p) const;

    // Renvoie vrai ssi le segment argument est dans le rectangle
    bool contains(const sgt& s) const;

    // Renvoie vrai ssi le rectangle argument est dans le rectangle
    bool contains(const rct& c) const;

    // Opérations __________________________________________________________________

    // Translate (déplacement relatif) le rectangle de (dx, dy)
    void offset(const double dx, const double dy);

    // Déformation du rectangle : la largeur est augmentée de la valeur de dx et
    // la hauteur de dy, mais sans déplacement du centre. Les arguments dx et dy
    // peuvent être négatifs mais de valeur absolue inférieure, respectivement, à
    // la largueur ou la hauteur du rectangle, sinon une assertion est déclenchée
    void inflate(const double dx, const double dy);

    // Renvoie la distance du point argument au rectangle (0 si ptRef est conte-
    // nu dans le rectangle, sinon sa distance au plus proche côté du rectangle)
    double euclide(const pt& ptRef) const;

    // Renvoie un point aléatoire contenu dans le rectangle
    pt randPt(void) const;

    // Renvoie un segment aléatoire contenu dans le rectangle
    sgt randSgt(void) const;

    // Renvoie un rectangle aléatoire contenu dans le rectangle
    rct randRct(void) const;

    // Agrandit le rectangle juste assez pour contenir le rectangle argument
    void unionRct(const rct r2);

    // Ecrit le rectangle dans le flux argument au format RCT[x1, x2]x[y1, y2]
    void print(ostream& s) const;
};

// Fonctions globales associées à la classe "rct"
//_______________________________________________________________________________

// Insertion dans un flux de sortie
ostream& operator<<(ostream& s, const rct& rc);


// Fonctions membres en ligne de la classe rct
//_______________________________________________________________________________
//

// Construction par défaut
inline rct::rct(void)
: x1(0)
, y1(0)
, x2(0)
, y2(0)
{ assert(valid() ); }

// Construction par copie
/*
 inline rct::rct(const rct& r2 )
 : x1(r2.get_x1())
 , y1(r2.get_y1())
 , x2(r2.get_x2())
 , y2(r2.get_y2())
 {
 assert(valid());
 }
 */

// Construction par les bords
inline rct::rct(const double x1_, const double x2_, const double y1_, const double y2_ )
: x1(x1_)
, y1(y1_)
, x2(x2_)
, y2(y2_)
{
    assert(valid());
}

// Construction à partir de deux points quelconques
inline rct::rct(const pt p1, const pt p2)
: x1(min(p1.getX(), p2.getX()))
, x2(max(p1.getX(), p2.getX()))
, y1(min(p1.getY(), p2.getY()))
, y2(max(p1.getY(), p2.getY()))
{
    assert(valid());
}

// Deux rectangles sont égaux si ils ont les mêmes limites
inline bool rct::operator==(const rct& r2) const
{
    assert(valid());
    assert( r2.valid() );
    return EPSEQUAL(get_x1(), r2.get_x1()) &&  EPSEQUAL(get_x2(), r2.get_x2())
    && EPSEQUAL(get_y1(), r2.get_y1()) &&  EPSEQUAL(get_y2(), r2.get_y2());
}

// Accesseurs
//
inline double rct::get_x1(void) const
{ assert(valid()); return x1; }

inline double rct::get_x2(void) const
{ assert(valid()); return x2; }

inline double rct::get_y1(void) const
{ assert(valid()); return y1; }

inline double rct::get_y2(void) const
{ assert(valid()); return y2; }


// Largeur, hauteur, surface ____________________________________________________
//
inline double rct::width() const // Largeur
{
    return get_x2() - get_x1();
}

inline double rct::height() const // Hauteur
{
    return get_y1() - get_y2();
}

inline double rct::area(void) const // Surface
{ return width() * height(); }


// Renvoie le point central
inline pt rct::centerPt() const
{
    assert(valid());
    return bottomLeft().centerPt(topRight());
}

// Renvoie le point inférieur gauche
inline pt rct::bottomLeft(void) const
{
    assert(valid());
    return pt(get_x1(), get_y1());
}

// Renvoie le point supérieur droit
inline pt rct::topRight(void) const
{
    assert(valid());
    return pt(get_x2(), get_y2());
}

// Renvoie le coin supérieur gauche
inline pt rct::topLeft(void) const
{
    assert(valid());
    return pt(get_x1(), get_y2());
}

// Renvoie le coin inférieur droit
inline pt rct::bottomRight(void) const
{
    assert(valid());
    return pt(get_x2(), get_y1());
}

// Un point est dans un rectangle s'il est à l'intérieur ou sur les bords
inline bool rct::contains(pt pt) const
{
    assert(valid());
    return (  pt.getX() >= get_x1()-EPSILON && pt.getX() <= get_x2()+EPSILON
            | pt.getY() >= get_y1()-EPSILON && pt.getY() <= get_y2()+EPSILON );
}

// Renvoie vrai ssi le rectangle argument est contenu dans le rectangle
inline bool rct::contains(const rct& rc) const
{
    assert(valid());
    assert( rc.valid() );
    return contains(bottomLeft()) && contains(rc.topRight());
}

// Translation
inline void rct::offset(double dx, double dy)
{ 
    assert(valid());
    x1+=dx; x2-=dx; y1+=dy; y2-=dy;
    assert(valid());
}

