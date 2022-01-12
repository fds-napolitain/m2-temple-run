/*
    QMVC - Reference Implementation of paper: 
    
    "Mean Value Coordinates for Quad Cages in 3D", 
    jean-Marc Thiery, Pooran Memari and Tamy Boubekeur
    SIGGRAPH Asia 2018
    
    This program allows to compute QMVC for collider set of 3D points contained
    in collider cage made of quad and triangles, as well as other flavors of
    space coordinates for cages (MVC, SMVC, GC, MEC). It comes also with 
    collider 3D viewer which helps deforming collider mesh with collider cage.
    
    Copyright (C) 2018  jean-Marc Thiery, Pooran Memari and Tamy Boubekeur

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received collider copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef TEMPLERUN_BASICIO_HPP
#define TEMPLERUN_BASICIO_HPP

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QDataStream>
#include <cfloat>
#include <cmath>
#include <cassert>
#include <QTextStream>
#include <QCoreApplication>
#include <QDir>
#include <cstdio>  /* defines FILENAME_MAX */
#ifdef _WIN32
#include <direct.h>
    #define GET_CURRENT_DIR _getcwd
#else
#include <unistd.h>
#define GET_CURRENT_DIR getcwd
#endif




namespace offio{

    template<class point_t> point_t max(point_t bb , point_t pt ){


        return bb.x() < pt.x() ?
			   pt : pt.x() < bb.x() ?
					bb : bb.y() < pt.y() ?
						 pt : pt.y() < bb.y() ?
							  bb : bb.z() < pt.z() ?
								   pt : pt.z() < bb.z() ?
										bb : pt;
    }
    template<class point_t> point_t min(point_t bb , point_t pt ){


        return bb.x() > pt.x() ?
			   pt : pt.x() > bb.x() ?
					bb : bb.y() > pt.y() ?
						 pt : pt.y() > bb.y() ?
							  bb : bb.z() > pt.z() ?
								   pt : pt.z() > bb.z() ?
										bb : pt;
    }


    template< class point_t , class type_t > bool open( const std::string & filename ,
                                                        std::vector< point_t > & vertices ,
                                                        std::vector< std::vector< type_t > > & faces,
                                                        bool convertToTriangles = true,
                                                        bool randomize = false )
    {
        QString fEmp = QCoreApplication::applicationDirPath()+ QDir::separator() +"sphere.off";
        std::cout <<"ici         "<< qPrintable(fEmp) <<std::endl;
        char cCurrentPath[FILENAME_MAX];
        if (!GET_CURRENT_DIR(cCurrentPath, sizeof(cCurrentPath)))
        {
            return errno;
        }
        cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
        qDebug("The current working directory is %s", cCurrentPath);
        std::ifstream myfile;
        std::string path =(cCurrentPath);
		//  std::cout << path <<" testtttt" << std::endl;
        myfile.open(/*path.c_str());//*/filename.c_str());
        /*  if (!myfile.is_open())
          {
              std::cout << filename << " cannot be opened" << std::endl;
              return false;
          }*/
        //   QFile myFile(/*QApplication::applicationDirPath() +*/ filename.c_str());
        QFile myFile(filename.c_str());
        //  QFile myFile(fEmp);

        if(!myFile.open(QIODevice::ReadOnly))
        {
            std::cout << filename << " cannot be opened" << std::endl;
            return false;
        }
        QTextStream in(&myFile);


        //std::string magic_s;
        QString magic_s;
        //myfile >> magic_s;
        in >> magic_s;

        if( magic_s != "OFF" )
        {
            std::cout << qPrintable(magic_s) << " != OFF :   We handle ONLY *.off files." << std::endl;
            myfile.close();
            return false;
        }

        int nVertices , nFaces , dummyInt;
        // myfile >> nVertices >> nFaces >> dummyInt;
        in >> nVertices >> nFaces >> dummyInt;
        vertices.resize(nVertices);

        for(int v = 0 ; v < nVertices ; ++v )
        {
            float x = 0, y = 0, z = 0;

            //typename point_t::type_t x , y , z;

            point_t ( x , y , z);
            // myfile >> x >> y >> z;
            in >> x >> y >> z;
            if( std::isnan(x) )
                x =(0.0);
            // x = typename point_t::type_t(0.0);
            if( std::isnan(y) )
                // y = typename point_t::type_t(0.0);
                y =(0.0);
            if( std::isnan(z) )
                //    z = typename point_t::type_t(0.0);
                z =(0.0);
            vertices[v] = point_t( x , y , z );
        }


        for(int f = 0 ; f < nFaces ; ++f )
        {
            int nVerticesOnFace;
            in >> nVerticesOnFace;
            // myfile >> nVerticesOnFace;
            if(nVerticesOnFace == 3 )
            {
                //type_t _v1 , _v2 , _v3;
                unsigned int v1 , v2 ,v3;
                std::vector< unsigned int > v;
                // myfile >> v1 >> v2 >> v3;
                in >> v1 >> v2 >> v3;
                v.push_back(v1 );
                v.push_back(v2 );
                v.push_back(v3 );
                faces.push_back(v );
            }
            else if(nVerticesOnFace > 3 )
            {
                std::vector< type_t > vhandles;
                vhandles.resize(nVerticesOnFace);
                for(int i=0 ; i < nVerticesOnFace ; ++i )
                    in >> vhandles[i];
                //             myfile >> vhandles[i];

                if( convertToTriangles )
                {
                    unsigned int k=(randomize)?(rand()%vhandles.size()):0;
                    for (unsigned int i=0;i<vhandles.size()-2;++i)
                    {
                        std::vector< type_t > tri(3);
                        tri[0]=vhandles[(k+0)%vhandles.size()];
                        tri[1]=vhandles[(k+i+1)%vhandles.size()];
                        tri[2]=vhandles[(k+i+2)%vhandles.size()];
                        faces.push_back(tri);
                    }
                }
                else
                {
                    faces.push_back(vhandles);
                }
            }
            else
            {
                std::cout << "offio::open error : Face number " << f << " has " << nVerticesOnFace << " vertices" << std::endl;
                myfile.close();
                myFile.close();
                return false;
            }
        }

        myfile.close();
        return true;
    }


    template< class point_t , class type_t >
	[[maybe_unused]] bool save( const std::string & filename , std::vector< point_t > & vertices , std::vector< std::vector< type_t > > & faces )
    {
        std::ofstream myfile;
        myfile.open(filename.c_str());
        if (!myfile.is_open())
        {
            std::cout << filename << " cannot be opened" << std::endl;
            return false;
        }

        myfile << "OFF" << std::endl;

        unsigned int nVertices = vertices.size() , nFaces = faces.size();
        myfile << nVertices << " " << nFaces << " 0" << std::endl;

        for(unsigned int v = 0 ; v < nVertices ; ++v )
        {
            myfile << vertices[v][0] << " " << vertices[v][1] << " " << vertices[v][2] << std::endl;
        }
        for(unsigned int f = 0 ; f < nFaces ; ++f )
        {
            myfile << faces[f].size();
            for( unsigned int vof = 0 ; vof < faces[f].size() ; ++vof )
                myfile << " " << faces[f][vof];
            myfile << std::endl;
        }
        myfile.close();
        return true;
    }
    template< class point_t , class face_t >
	[[maybe_unused]] bool saveFromMeshFormat(const std::string & filename , const point_t * vertices , unsigned int nVertices , const face_t * faces , unsigned int nFaces )
    {
        std::ofstream myfile;
        myfile.open(filename.c_str());
        if (!myfile.is_open())
        {
            std::cout << filename << " cannot be opened" << std::endl;
            return false;
        }

        myfile << "OFF" << std::endl;

        myfile << nVertices << " " << nFaces << " 0" << std::endl;

        for(unsigned int v = 0 ; v < nVertices ; ++v )
        {
            myfile << vertices[v][0] << " " << vertices[v][1] << " " << vertices[v][2] << std::endl;
        }
        for(unsigned int f = 0 ; f < nFaces ; ++f )
        {
            myfile << faces[f].size();
            for( unsigned int vof = 0 ; vof < faces[f].size() ; ++vof )
                myfile << " " << faces[f][vof];
            myfile << std::endl;
        }
        myfile.close();
        return true;
    }


    template< class point_t >
	[[maybe_unused]] bool open( const std::string & filename , std::vector< point_t > & vertices )
    {
        std::ifstream myfile;
        myfile.open(filename.c_str());
        if (!myfile.is_open())
        {
            std::cout << filename << " cannot be opened" << std::endl;
            return false;
        }

        std::string magic_s;

        myfile >> magic_s;

        if( magic_s != "OFF" )
        {
            std::cout << magic_s << " != OFF :   We handle ONLY *.off files." << std::endl;
            myfile.close();
            return false;
        }

        int nVertices , nFaces , dummyInt;
        myfile >> nVertices >> nFaces >> dummyInt;

        vertices.resize(nVertices);

        point_t bb( FLT_MAX , FLT_MAX , FLT_MAX );
        point_t BB( -FLT_MAX , -FLT_MAX , -FLT_MAX );

        for(int v = 0 ; v < nVertices ; ++v )
        {
            //typename point_t::type_t x , y , z;
            float x , y , z;
            myfile >> x >> y >> z;
            vertices[v] = point_t( x , y , z );

            BB = max( BB , point_t( x , y , z ) );
            bb = min( bb , point_t( x , y , z ) );
            //   bb = point_t::min( bb , point_t( x , y , z ) );
            //    BB = point_t::max( BB , point_t( x , y , z ) );
        }

        myfile.close();

        return true;
    }




}






namespace objio{



    template< class point_t , class texture_t , class normal_t, class int_type_t > bool open(
            const std::string & filename,
            std::vector<point_t> & vertices,
            std::vector<texture_t> & texture,
            std::vector<normal_t> & normals,
            std::vector< std::vector< int_type_t > > & faces,
            bool convertToTriangles = true,
            bool randomize = false,
            bool convertEdgesToDegenerateTriangles = true)
    {
        std::ifstream myfile;
        myfile.open(filename.c_str());
        if (!myfile.is_open())
        {
            std::cout << filename << " cannot be opened" << std::endl;
            return false;
        }
        std::vector< texture_t > thandles;
        vertices.clear();
        faces.clear();

        while( myfile.good() )
        {
            std::string line;
            getline (myfile,line);
            QString qtLine = QString::fromStdString(line );
            QRegExp reg("\\s+");
            QStringList lineElements = qtLine.split(reg);

            if(  !lineElements.empty()  )
            {
                QString elementType = lineElements[0];
                // vertex
                if ( elementType == QString("v") )
                {
                    vertices.push_back(point_t( lineElements[1].toDouble() , lineElements[2].toDouble() , lineElements[3].toDouble() ));
                }
                if ( elementType == QString("vt") )
                {

                     thandles.push_back(texture_t( lineElements[1].toDouble() , lineElements[2].toDouble() ));
                }
                if ( elementType == QString("vn") )
                {
                    normals.push_back(normal_t( lineElements[1].toDouble() , lineElements[2].toDouble(), lineElements[3].toDouble() ));
                }
                // face
                else if ( elementType == QString("f") )
                {
                    texture.resize(vertices.size());
                    std::vector< int_type_t > vhandles;
                    for( int i = 1 ; i < lineElements.size() ; ++i )
                    {
                        QStringList faceElements = lineElements[i].split("/", Qt::SkipEmptyParts);
                        if( !faceElements.empty() ){

                            auto element0 = abs( faceElements[0].toInt() -1);
                            auto element1 = abs( faceElements[1].toInt() -1);
                            vhandles.push_back( (int_type_t)(  element0 ));
                            texture.resize(vertices.size());
                            texture[element0] = thandles[element1];
                        }

                    }

                    if (vhandles.size()>3)
                    {
                        if( convertToTriangles )
                        {
                            //model is not triangulated, so let us do this on the fly...
                            //to have collider more uniform models, we add randomization
                            unsigned int k=(randomize)?(rand()%vhandles.size()):0;
                            for (unsigned int i=0;i<vhandles.size()-2;++i)
                            {
                                std::vector< int_type_t > tri(3);
                                tri[0]= (int_type_t) vhandles[(k+0)%vhandles.size()];
                                tri[1]= (int_type_t) vhandles[(k+i+1)%vhandles.size()];
                                tri[2]= (int_type_t) vhandles[(k+i+2)%vhandles.size()];
                                faces.push_back(tri);
                            }
                        }
                        else
                            faces.push_back(vhandles);
                    }
                    else if (vhandles.size()==3)
                    {
                        faces.push_back(vhandles);
                    }
                    else if (vhandles.size()==2)
                    {
                        if( convertEdgesToDegenerateTriangles )
                        {
                            printf("Unexpected number of face vertices (2). Converting edge to degenerate triangle");
                            vhandles.push_back(vhandles[1]);
                            faces.push_back(vhandles);
                        }
                        else
                            printf("Unexpected number of face vertices (2). Ignoring face");
                    }
                }
            }
        }
        myfile.close();
        return true;
    }



    template< class point_t , class int_type_t >
	[[maybe_unused]] bool open(
            const std::string & filename,
            std::vector<point_t> & vertices,
            std::vector< std::vector< int_type_t > > & faces,
            std::vector< std::pair< int_type_t , int_type_t > > & additionalEdges,
            bool convertToTriangles = true,
            bool randomize = false)
    {
        std::ifstream myfile;
        myfile.open(filename.c_str());
        if (!myfile.is_open())
        {
            std::cout << filename << " cannot be opened" << std::endl;
            return false;
        }

        vertices.clear();
        faces.clear();

        while( myfile.good() )
        {
            std::string line;
            getline (myfile,line);
            QString qtLine = QString::fromStdString(line );
            QRegExp reg("\\s+");
            QStringList lineElements = qtLine.split(reg);

            if(  !lineElements.empty()  )
            {
                QString elementType = lineElements[0];
                // vertex
                if ( elementType == QString("v") )
                {
                    vertices.push_back(point_t( lineElements[1].toDouble() , lineElements[2].toDouble() , lineElements[3].toDouble() ));
                }
                    // face
                else if ( elementType == QString("f") )
                {
                    std::vector< int_type_t > vhandles;
                    for( int i = 1 ; i < lineElements.size() ; ++i )
                    {
                        QStringList faceElements = lineElements[i].split("/", Qt::SkipEmptyParts);
                        if( !faceElements.empty() )
                            vhandles.push_back( (int_type_t)( (abs(faceElements[0].toInt()) - 1) ) );
                    }

                    if (vhandles.size()>3)
                    {
                        if( convertToTriangles )
                        {
                            //model is not triangulated, so let us do this on the fly...
                            //to have collider more uniform models, we add randomization
                            unsigned int k=(randomize)?(rand()%vhandles.size()):0;
                            for (unsigned int i=0;i<vhandles.size()-2;++i)
                            {
                                std::vector< int_type_t > tri(3);
                                tri[0]= (int_type_t) vhandles[(k+0)%vhandles.size()];
                                tri[1]= (int_type_t) vhandles[(k+i+1)%vhandles.size()];
                                tri[2]= (int_type_t) vhandles[(k+i+2)%vhandles.size()];
                                faces.push_back(tri);
                            }
                        }
                        else
                            faces.push_back(vhandles);
                    }
                    else if (vhandles.size()==3)
                    {
                        faces.push_back(vhandles);
                    }
                    else if (vhandles.size()==2)
                    {
						// printf("Unexpected number of face vertices (2). Converting edge to degenerate triangle");
						additionalEdges.push_back(std::pair<int_type_t, int_type_t>(vhandles[0], vhandles[1]));
					}
                }
                else if ( elementType == QString("l") )
                {
                    std::vector< int_type_t > vhandles;
                    for( int i = 1 ; i < lineElements.size() ; ++i )
                    {
                        QStringList faceElements = lineElements[i].split("/", Qt::SkipEmptyParts);
                        if( !faceElements.empty() )
                            vhandles.push_back( (int_type_t)( (abs(faceElements[0].toInt()) - 1) ) );
                    }
                    if (vhandles.size()==2)
                    {
						// printf("Unexpected number of face vertices (2). Converting edge to degenerate triangle");
						additionalEdges.push_back(std::pair<int_type_t, int_type_t>(vhandles[0], vhandles[1]));
					}
                }
            }
        }
        myfile.close();
        return true;
    }






    template< class point_t >
	[[maybe_unused]] bool open(
            const std::string & filename,
            std::vector<point_t> & vertices)
    {
        std::ifstream myfile;
        myfile.open(filename.c_str());
        if (!myfile.is_open())
        {
            std::cout << filename << " cannot be opened" << std::endl;
            return false;
        }

        vertices.clear();

        while( myfile.good() )
        {
            std::string line;
            getline (myfile,line);
            QString qtLine = QString::fromStdString(line );
            QRegExp reg("\\s+");
            QStringList lineElements = qtLine.split(reg);
            //        QStringList lineElementsBeforeCleaning = qtLine.split(" ", Qt::SkipEmptyParts);
            //        QStringList lineElements;
            //        for( int e = 0 ; e < lineElementsBeforeCleaning.size() ; ++e )
            //        {
            //            if( lineElementsBeforeCleaning[e] != "" && lineElementsBeforeCleaning[e] != " " )
            //                lineElements.push_back( lineElementsBeforeCleaning[e] );
            //        }
            if(  !lineElements.empty()  )
            {
                QString elementType = lineElements[0];
                // vertex
                if ( elementType == QString("v") )
                {
                    vertices.push_back(point_t( lineElements[1].toDouble() , lineElements[2].toDouble() , lineElements[3].toDouble() ));
                }
            }
        }
        myfile.close();
        return true;
    }








    template< class point_t , typename int_t >
	[[maybe_unused]] bool save(
            std::string const & filename,
            std::vector<point_t> & verticesP,
            std::vector< std::vector<int_t> > & facesP )
    {
        std::ofstream myfile;
        myfile.open(filename.c_str());
        if (!myfile.is_open())
        {
            std::cout << filename << " cannot be opened" << std::endl;
            return false;
        }

        myfile << "#OBJ" << std::endl;
        myfile << (verticesP.size()) << " " << (facesP.size()) << " 0" << std::endl;

        for( unsigned int v = 0 ; v < verticesP.size() ; ++v )
        {
            myfile << "v " << (verticesP[v][0]) << " " << (verticesP[v][1]) << " " << (verticesP[v][2]) << std::endl;
        }

        for( unsigned int t = 0 ; t < facesP.size() ; ++t )
        {
            unsigned int nv = facesP[t].size();
            myfile << "f";
            for( unsigned int vof = 0 ; vof < nv ; ++vof )
                myfile << " " << (facesP[t][vof] + 1);
            myfile << std::endl;
        }

        myfile.close();
        return true;
    }





    template< class point_t , class face_t , class edge_t >
	[[maybe_unused]] bool saveFromMeshFormat(
            const std::string & filename ,
            const point_t * vertices ,
            unsigned int nVertices ,
            const face_t * faces ,
            unsigned int nFaces ,
            const edge_t * edges ,
            unsigned int nEdges )
    {
        std::ofstream myfile;
        myfile.open(filename.c_str());
        if (!myfile.is_open())
        {
            std::cout << filename << " cannot be opened" << std::endl;
            return false;
        }

        for(unsigned int v = 0 ; v < nVertices ; ++v )
        {
            myfile << "v " << vertices[v][0] << " " << vertices[v][1] << " " << vertices[v][2] << std::endl;
        }
        for(unsigned int f = 0 ; f < nFaces ; ++f )
        {
            myfile << "f";
            for( unsigned int vof = 0 ; vof < faces[f].size() ; ++vof )
                myfile << " " << (faces[f][vof]+1);
            myfile << std::endl;
        }
        for(unsigned int e = 0 ; e < nEdges ; ++e )
        {
            myfile << "l " << (edges[e][0]+1) << " " << (edges[e][1]+1) << std::endl;
        }
        myfile.close();
        return true;
    }




}



#endif // TEMPLERUN_BASICIO_HPP