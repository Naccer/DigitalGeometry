#ifndef OBJECTDISCRETIZATION_H
#define OBJECTDISCRETIZATION_H


#include <iostream>
#include <math.h>
#include <fstream>

#include "DGtal/base/Common.h"
#include "DGtal/shapes/GaussDigitizer.h"
#include "DGtal/topology/LightImplicitDigitalSurface.h"
#include "DGtal/topology/DigitalSurface.h"
#include "DGtal/io/boards/Board2D.h"
#include "DGtal/shapes/Shapes.h"
#include "DGtal/shapes/implicit/ImplicitBall.h"
#include "DGtal/shapes/EuclideanShapesDecorator.h"
#include "DGtal/base/IteratorFunctions.h"
#include "DGtal/geometry/curves/GridCurve.h"
#include "DGtal/base/Circulator.h"
#include "DGtal/base/IteratorFunctions.h"
#include "DGtal/base/IteratorAdapter.h"
#include "DGtal/topology/helpers/Surfaces.h"
#include "DGtal/shapes/ShapeFactory.h"
#include "DGtal/io/Color.h"
#include "Board/Board.h"

using namespace std;
using namespace DGtal;
using namespace Z2i;

typedef ImplicitBall< Z2i::Space > DiskShape;
typedef ImplicitBall< Z3i::Space > SphereShape;
typedef EuclideanShapesCSG<DiskShape, DiskShape> EuclideanDisks;
typedef EuclideanShapesCSG<SphereShape, SphereShape> EuclideanSpheres;


class ObjectDiscretization
{
    public:
        ObjectDiscretization(string input_parameters,string erros,string areas);
        virtual ~ObjectDiscretization();
        void discretizationDeltaCalculus();
        Z2i::DigitalSet discretizeShape(EuclideanDisks shape, char* nameImage, Color color);
        double interPixelBorder(Z2i::DigitalSet shapeSet,  char* nameImage, Color color);
        double computeArea(Z2i::DigitalSet shapeSet);



    private:
        double delta_area[5];
        double delta_perimeter[5];

        RealPoint* lowerBound;
        RealPoint* upperBound;
        Domain* domain;
        double h ;
};

#endif // OBJECTDISCRETIZATION_H
