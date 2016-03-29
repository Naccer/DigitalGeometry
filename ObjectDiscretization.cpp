#include "ObjectDiscretization.h"

ObjectDiscretization::ObjectDiscretization(string inputs,string erros,string areas)
{
    ifstream input_parameters("inputs.txt");
	float lb;
	float ub;
	float size;
	input_parameters>>lb;
	//cout<<lb;

	input_parameters>>ub;
	//cout<<ub;
	input_parameters>>size;
	//cout<<size;
	input_parameters.close();


    lowerBound = new RealPoint(lb, lb);
    upperBound = new RealPoint(ub, ub);
    domain = new Domain(*lowerBound, *upperBound);
    h = 1/size;
    discretizationDeltaCalculus();

}



ObjectDiscretization::~ObjectDiscretization()
{
    delete lowerBound;
    delete upperBound;
    delete domain;
}




void ObjectDiscretization::discretizationDeltaCalculus()
{


    double cx = 0.0;
    double cy = 0.0;
    double radius = 5.0;
    DiskShape c( Z2i::RealPoint(cx, cy), radius );
    EuclideanDisks disk(c);


    Board2D board_disk(Color( 255, 255, 0 ));
    board_disk << SetMode( domain->className() , "Paving")
                << *domain;
    board_disk.setPenColorRGBf (1.0, 0, 0, 1.0f);
    board_disk.fillCircle ( cx, cy, radius, -1);
    board_disk.saveSVG("./generated/disk.svg");


    std::cout << "\nDisk\n\n";
    Z2i::DigitalSet diskSet = discretizeShape(disk, "./discretized/disk.svg", Color( 255, 0, 0, 255 ));

    double perimeter_disk_discrete = interPixelBorder(diskSet, "./borders/disk.svg", Color( 255, 0, 0, 255 ));
    double perimeter_disk_continuous = M_PI * 2 * radius;
    double delta_perimeter_disk = perimeter_disk_continuous - perimeter_disk_discrete;

    delta_perimeter[0] = delta_perimeter_disk;

    double area_disk_discrete = computeArea(diskSet);
    double area_disk_continuous = M_PI * (radius*radius);
    double error_area_disk = area_disk_continuous - area_disk_discrete;

    delta_area[0] = error_area_disk;


    double cx1 = -5.0;
    double cy1 = 0.0;
    double radius1 = 2;

    double cx2 = 3;
    double cy2 = 0.0;
    double radius2 = 4;

    DiskShape c1( Z2i::RealPoint(cx1, cy1), radius1);
    DiskShape c2( Z2i::RealPoint(cx2, cy2), radius2);
    EuclideanDisks two_disks(c1);
    two_disks.plus(c2);


    Board2D board_two_disks(Color( 0, 255, 0 ));
    board_two_disks << SetMode( domain->className(), "Paving" )
                << *domain;
    board_two_disks.setPenColorRGBf (1, 0, 0, 1.0f);
    board_two_disks.fillCircle( cx1, cy1, radius1, -1);
    board_two_disks.fillCircle( cx2, cy2, radius2, -1);
    board_two_disks.saveSVG("./generated/two_disks.svg");


    std::cout << "Two disks\n\n";
    Z2i::DigitalSet two_disks_Set = discretizeShape(two_disks, "./discretized/two_disks.svg", Color( 255, 0, 0, 255 ));

    double two_disks_perimeter_discrete = interPixelBorder(two_disks_Set, "./borders/two_disks.svg", Color( 255, 0, 0, 255 ));
    double two_disks_perimeter_continuous = M_PI * 2 * radius1 + M_PI * 2 * radius2;
    double erros_two_disks_perimeter = two_disks_perimeter_continuous - two_disks_perimeter_discrete;

    delta_perimeter[1] = erros_two_disks_perimeter;

    double two_disks_area_discrete = computeArea(two_disks_Set);
    double two_disks_area_continuous = M_PI * (radius1*radius1) + M_PI * (radius2*radius2);
    double error_two_disks_area = two_disks_area_continuous - two_disks_area_discrete;

	delta_area[1] = error_two_disks_area;


    cx1 = -2.0;
    cy1 = 0.0;
    radius1 = 3;

    cx2 = 2;
    cy2 = 0.0;
    radius2 = 3;

    DiskShape c3( Z2i::RealPoint(cx1, cy1), radius1);
    DiskShape c4( Z2i::RealPoint(cx2, cy2), radius2);
    EuclideanDisks overlapped_disks(c3);
    overlapped_disks.plus(c4);


    Board2D board_two_overlapped_disks;
    board_two_overlapped_disks << SetMode( domain->className(), "Paving" )
                << *domain;
    board_two_overlapped_disks.setPenColorRGBf (1, 0, 0, 1.0f);
    board_two_overlapped_disks.fillCircle( cx1, cy1, radius1, -1);
    board_two_overlapped_disks.fillCircle( cx2, cy2, radius2, -1);
    board_two_overlapped_disks.saveSVG("./generated/two_intersect_disks.svg");


    std::cout << "Overlaped disks\n\n";
    Z2i::DigitalSet overlapped_disks_Set = discretizeShape(overlapped_disks,"./discretized/two_intersect_disks.svg", Color( 255, 0, 0, 255 ));

    double overlapped_disks_perimeter_discrete = interPixelBorder(overlapped_disks_Set, "./borders/btwo_intersect_disks.svg", Color( 255, 0, 0, 255 ));
    double overlapped_disks_perimeter_continuous = (0.75)*(M_PI*2*radius1) + (0.75)*(M_PI*2*radius2) ;
    double error_overlapped_disks_perimeter = overlapped_disks_perimeter_continuous - overlapped_disks_perimeter_discrete;
    delta_perimeter[2] = error_overlapped_disks_perimeter;

    double overlapped_disks_area_discrete = computeArea(overlapped_disks_Set);
    double intersection_area = 6.195;
    double overlapped_disks_area_continuous = M_PI * (radius1*radius1) + M_PI * (radius2*radius2) - intersection_area;
    double error_overlapped_disks_area = two_disks_area_continuous - two_disks_area_discrete;

    delta_area[2] = error_overlapped_disks_area;


    cx1 = 0.0;
    cy1 = 0.0;
    radius1 = 3;

    cx2 = 0.0;
    cy2 = 0.0;
    radius2 = 1;

    DiskShape c5( Z2i::RealPoint(cx1, cy1), radius1);
    DiskShape c6( Z2i::RealPoint(cx2, cy2), radius2);
    EuclideanDisks  sub_disks_1(c5);
    sub_disks_1.minus(c6);

    Board2D board_sub_disks_1;
    board_sub_disks_1 << SetMode( domain->className(), "Paving" )
                << *domain;
    board_sub_disks_1.setPenColorRGBf (1, 0, 0, 1.0f);
    board_sub_disks_1.fillCircle( cx1, cy1, radius1, -1);
    board_sub_disks_1.setPenColorRGBf (1,1, 1, 1.0f);
    board_sub_disks_1.fillCircle( cx2, cy2, radius2, -1);
    board_sub_disks_1.saveSVG("./generated/sub_disks_1_continuous.svg");

    std::cout<<"Sub. disks 1\n\n";
    Z2i::DigitalSet sub_disks_1_Set = discretizeShape(sub_disks_1, "./discretized/sub_disks_1.svg", Color( 255, 0, 0, 255 ));

    double sub_disks_1_perimeter_discrete = interPixelBorder(sub_disks_1_Set,  "./borders/border_sub_disks_1.svg", Color( 255, 0, 0, 255 ));
    double sub_disks_1_perimeter_continuous = M_PI * 2 * radius1 + M_PI * 2 * radius2;
    double erros_sub_disks_1_perimeter = sub_disks_1_perimeter_continuous - sub_disks_1_perimeter_discrete;

    delta_perimeter[3] = erros_sub_disks_1_perimeter;

    double sub_disks_1_area_discrete = computeArea(sub_disks_1_Set);
    double sub_disks_1_area_continuous = M_PI * (radius1*radius1) - M_PI * (radius2*radius2);
    double error_sub_disks_1_area = sub_disks_1_area_continuous - sub_disks_1_area_discrete;

    delta_area[3]= error_sub_disks_1_area;


    cx1 = 0.0;
    cy1 = 0.0;
    radius1 = 6.0;

    cx2 = 2.0;
    cy2 = 0.0;
    radius2 = 4;

    DiskShape c7( Z2i::RealPoint(cx1, cy1), radius1);
    DiskShape c8( Z2i::RealPoint(cx2, cy2), radius2);
    EuclideanDisks  sub_disks_2(c7);
    sub_disks_2.minus(c8);


    Board2D board_sub_disks_2;
    board_sub_disks_2 << SetMode( domain->className(), "Paving" )
                << *domain;
    board_sub_disks_2.setPenColorRGBf (1, 0.0, 0, 1.0f);
    board_sub_disks_2.fillCircle( cx1, cy1, radius1, -1);
    board_sub_disks_2.setPenColorRGBf (1, 1, 1, 1.0f);
    board_sub_disks_2.fillCircle( cx2, cy2, radius2, -1);
    board_sub_disks_2.saveSVG("./generated/sub_disks_2_continuous.svg");

    std::cout<<"Sub. disks 2\n\n";
    Z2i::DigitalSet sub_disks_2_Set = discretizeShape(sub_disks_2, "./discretized/sub_disks_2.svg", Color( 255, 0, 0, 255 ));

    double sub_disks_2_perimeter_discrete = interPixelBorder(sub_disks_2_Set, "./borders/border_sub_disks_1.svg", Color( 255, 0, 0, 255 ));
    double sub_disks_2_perimeter_continuous = M_PI * 2 * radius1 + M_PI * 2 * radius2;
    double erros_sub_disks_2_perimeter = sub_disks_2_perimeter_continuous - sub_disks_2_perimeter_discrete;

    delta_perimeter[4] = erros_sub_disks_2_perimeter;

    double sub_disks_2_area_discrete = computeArea(sub_disks_2_Set);
    double sub_disks_2_area_continuous = M_PI * (radius1*radius1) - M_PI * (radius2*radius2);
    double error_sub_disks_2_area = sub_disks_2_area_continuous - sub_disks_2_area_discrete;

    delta_area[4] = error_sub_disks_2_area;



}

double ObjectDiscretization::computeArea(Z2i::DigitalSet shapeSet)
{

    double area = 0;

    typedef DigitalSet::ConstIterator ConstIterator2;
    ConstIterator2 iterator2 = shapeSet.begin();

    while (iterator2 != shapeSet.end())
    {
		area += 1;
		++iterator2;
    }

    area = area*(pow(h, 2));
    std::cout << "	Total area: " << area << "\n\n";

    return area;
}


Z2i::DigitalSet ObjectDiscretization::discretizeShape(EuclideanDisks shape, char* nameImage, Color color)
{

    typedef GaussDigitizer< Z2i::Space, EuclideanDisks > MyGaussDigitizer;
    MyGaussDigitizer digShape;
    digShape.attach( shape );
    digShape.init( *lowerBound, *upperBound ,h);
    Z2i::Domain domainShape = digShape.getDomain();
    Z2i::DigitalSet shapeSet( domainShape );
    Shapes<Z2i::Domain>::digitalShaper(shapeSet, digShape);


    Board2D boardShape;
    boardShape << SetMode( domainShape.className(), "Paving" )
                << domainShape;

    boardShape << CustomStyle( shapeSet.className(), new CustomFillColor( color ));
    boardShape << shapeSet;
    boardShape.saveSVG ( nameImage );

    return shapeSet;
}



double ObjectDiscretization::interPixelBorder(Z2i::DigitalSet shapeSet,  char* nameImage, Color color)
{

	std::vector< std::vector< SCell > > aVectConnectedSCell;
	K2 ks;
    ks.init( *lowerBound/h, *upperBound/h, true );
    SurfelAdjacency<K2::dimension> sAdj( true );
	DGtal::Surfaces< Z2i::KSpace >::extractAllConnectedSCell(aVectConnectedSCell, ks, sAdj, shapeSet, false);
	std::cout << "	Number of connected components: " << (const int) aVectConnectedSCell.size() << "\n\n";


	Z2i::Domain domain(*lowerBound/h, *upperBound/h);

    Board2D boardBorder;
    boardBorder << SetMode( domain.className(), "Paving" )
                <<  domain;

	double perimeter_total = 0;


	for (int i = 0; i < (const int) aVectConnectedSCell.size(); i++)
	{
		Curve borderInterPixel( ks );
		double perimeter = aVectConnectedSCell.at(i).size() * h;
		perimeter_total += perimeter;
		std::cout << "	Component " << i << "\n\n";
		cout << "		Perimeter: " << perimeter << "\n\n";

		for (int j = 0; j <  (const int) aVectConnectedSCell.at(i).size(); j++)
		{
			boardBorder<< CustomStyle( aVectConnectedSCell.at(i).at(j).className(), new CustomFillColor(color) );
			boardBorder << aVectConnectedSCell.at(i).at(j);
		}

	}

	boardBorder.saveSVG(nameImage);

	return perimeter_total;
}

