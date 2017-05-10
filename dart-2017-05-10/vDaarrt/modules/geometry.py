'''
@auhtor : Corentin R
@date : February 2015

This file contains geometric objects' constructors. Nothing should be changed
in this file as it would possibly change the comportment of the robot

Modified BenBlop 2016, may 

'''
import math
import pylygon
#from numpy import array
from constantes import *
from numpy import array, cos, dot, fabs, lexsort, pi, sin, sqrt, vstack, linalg,nan
import geometry as geo

    
def createSonar(daarrt,sonitv):

    '''
    return :
        list of pylygon objects containing each sonar of the DAARRT

    arguments :
        daarrt object

    '''

    sonar=[]
    sonarLoc=[]

    theta = daarrt.sonarAngle*math.pi/180.0


    for i in range(daarrt.nFrontSonar) :

        if daarrt.nFrontSonar>1 :
            x0 = daarrt.robotLenght/2 + 2
            y0 = daarrt.robotWidth*i/(daarrt.nFrontSonar-1) - daarrt.robotWidth/2
        else :
            x0 = daarrt.robotLenght/2 + 2
            y0 = 0

        ply=pylygon.Polygon([(x0,y0),(x0+sonarLenght*math.cos(theta),y0+sonarLenght*math.sin(theta)),(x0+sonarLenght*math.cos(-theta),y0+sonarLenght*math.sin(-theta))])
        ivtx = pylygon.Polygon([(x0,y0)])
        sonarLoc.append(ivtx)
        sonar.append(ply)
        
    for i in range (daarrt.nBackSonar) :
        if daarrt.nBackSonar >1 :
            x0 = -daarrt.robotLenght/2 + 2
            y0 = daarrt.robotWidth*i/(daarrt.nBackSonar-1) - daarrt.robotWidth/2
        else :
            x0 = -daarrt.robotLenght/2 + 2
            y0 = 0
        ply=pylygon.Polygon([(x0,y0),(-x0-sonarLenght*math.cos(theta),y0+sonarLenght*math.sin(theta)),(-x0-sonarLenght*math.cos(-theta),y0+sonarLenght*math.sin(-theta))])
        ivtx = pylygon.Polygon([(x0,y0)])
        sonarLoc.append(ivtx)
        sonar.append(ply)
        

    for i in range (daarrt.nLeftSonar):

        if daarrt.nLeftSonar>1 :
            x0 = -daarrt.robotLenght/2 + daarrt.wheelLenght/2 +  (daarrt.robotLenght-daarrt.robotWidth)*i/(daarrt.nLeftSonar-1)
            y0 = -daarrt.robotWidth/2 + 2
        else :
            x0 = 0
            y0=-daarrt.robotWidth/2 + 2

        ply=pylygon.Polygon([(x0,y0),(x0+sonarLenght*math.sin(theta),-y0-sonarLenght*math.cos(theta)),(x0+sonarLenght*math.sin(-theta),-y0-sonarLenght*math.cos(-theta))])
        ivtx = pylygon.Polygon([(x0,y0)])
        sonarLoc.append(ivtx)
        sonar.append(ply)


    for i in range (daarrt.nRightSonar):

        if daarrt.nRightSonar>1 :
            x0 = -daarrt.robotLenght/2 + daarrt.wheelLenght/2 +  (daarrt.robotLenght-daarrt.robotWidth)*i/(daarrt.nLeftSonar-1)
            y0 = daarrt.robotWidth/2 + 2
        else :
            x0 = 0
            y0=daarrt.robotWidth/2 + 2

        ply=pylygon.Polygon([(x0,y0),(x0+sonarLenght*math.sin(theta),+y0+sonarLenght*math.cos(theta)),(x0+sonarLenght*math.sin(-theta),+y0+sonarLenght*math.cos(-theta))])
        ivtx = pylygon.Polygon([(x0,y0)])
        sonarLoc.append(ivtx)
        sonar.append(ply)

    sonar=[poly_translate(poly_rotate(element,daarrt.robotCap),daarrt.posX,daarrt.posY) for element in sonar]
    sonarLoc=[poly_translate(poly_rotate(element,daarrt.robotCap),daarrt.posX,daarrt.posY) for element in sonarLoc]
    
    if sonitv == 0:
        return sonar
    else:
        return sonarLoc
    
def createSonarIntersect(daarrt):

    '''
    return :
        list of pylygon objects containing each sonar of the DAARRT

    arguments :
        daarrt object

    '''

    intersect=[]

    theta = daarrt.sonarAngle*math.pi/180.0


    for i in range(daarrt.nFrontSonar) :

        if daarrt.nFrontSonar>1 :
            x0 = daarrt.robotLenght/2 + 2
            y0 = daarrt.robotWidth*i/(daarrt.nFrontSonar-1) - daarrt.robotWidth/2
        else :
            x0 = daarrt.robotLenght/2 + 2
            y0 = 0

        intersect.append(pylygon.Polygon([(x0,y0-1),(x0,y0+1),(x0+50,y0)]))
        
    for i in range (daarrt.nBackSonar) :
        if daarrt.nBackSonar >1 :
            x0 = -daarrt.robotLenght/2 + 2
            y0 = daarrt.robotWidth*i/(daarrt.nBackSonar-1) - daarrt.robotWidth/2
        else :
            x0 = -daarrt.robotLenght/2 + 2
            y0 = 0
        intersect.append(pylygon.Polygon([(x0,y0-1),(x0,y0+1),(-x0-50,y0)]))

    for i in range (daarrt.nLeftSonar):

        if daarrt.nLeftSonar>1 :
            x0 = -daarrt.robotLenght/2 + daarrt.wheelLenght/2 +  (daarrt.robotLenght-daarrt.robotWidth)*i/(daarrt.nLeftSonar-1)
            y0 = -daarrt.robotWidth/2 + 2
        else :
            x0 = 0
            y0=-daarrt.robotWidth/2 + 2

        intersect.append(pylygon.Polygon([(x0-1,y0),(x0+1,y0),(x0,-y0-50)]))


    for i in range (daarrt.nRightSonar):

        if daarrt.nRightSonar>1 :
            x0 = -daarrt.robotLenght/2 + daarrt.wheelLenght/2 +  (daarrt.robotLenght-daarrt.robotWidth)*i/(daarrt.nLeftSonar-1)
            y0 = daarrt.robotWidth/2 + 2
        else :
            x0 = 0
            y0=daarrt.robotWidth/2 + 2

        intersect.append(pylygon.Polygon([(x0-1,y0),(x0+1,y0),(x0,y0+50)]))

    intersect=[poly_translate(poly_rotate(element,daarrt.robotCap),daarrt.posX,daarrt.posY) for element in intersect]

    return intersect

def createBody(daarrt,offsetX,offsetY):

    '''
    return :
        list corresponding to the daarrt's body

    arguments :
        daarrt object
        offsetX : optionnal offset on X axis
        offsetY : optionnal offset on Y axis

    '''

    x0 = offsetX
    y0 = offsetY
    x1 = offsetX + daarrt.robotLenght
    y1 = offsetY
    x2 = offsetX + daarrt.robotLenght
    y2 = offsetY + daarrt.robotWidth
    x3 = offsetX
    y3 = offsetY + daarrt.robotWidth
    body = [(x0,y0) , (x1,y1) , (x2,y2) , (x3,y3)]

    return body
    
    
def createFrontId(daarrt,offsetX,offsetY):

    '''
    return :
        list corresponding to the daarrt's body

    arguments :
        daarrt object
        offsetX : optionnal offset on X axis
        offsetY : optionnal offset on Y axis

    '''

    x0 = offsetX + daarrt.robotLenght/2
    y0 = offsetY
    x1 = offsetX + daarrt.robotLenght
    y1 = offsetY + daarrt.robotWidth/2.01
    x2 = offsetX + daarrt.robotLenght
    y2 = offsetY + daarrt.robotWidth/1.99
    x3 = offsetX + daarrt.robotLenght/2
    y3 = offsetY + daarrt.robotWidth

    frontId = [(x0,y0) , (x1,y1) , (x2,y2), (x3,y3)]

    return frontId

def createWheel(daarrt,offsetX,offsetY):

    '''
    return :
        list corresponding to a daarrt wheel

    arguments :
        daarrt object
        offsetX : optionnal offset on X axis
        offsetY : optionnal offset on Y axis

    '''
    x0 = offsetX
    y0 = offsetY
    x1 = offsetX
    y1 = offsetY - daarrt.wheelWidth
    x2 = offsetX + daarrt.wheelLenght
    y2 = offsetY - daarrt.wheelWidth
    x3 = offsetX + daarrt.wheelLenght
    y3 = offsetY
    wheel=[(x0,y0) , (x1,y1) , (x2,y2) , (x3,y3)]

    return wheel

def createClaw(daarrt,offsetX,offsetY):

    '''
    return :
        list corresponding to the daarrt's claw

    arguments :
        daarrt object
        offsetX : optionnal offset on X axis
        offsetY : optionnal offset on Y axis

    '''

    x0 = offsetX
    y0 = offsetY
    x1 = offsetX + daarrt.clawLenght
    y1 = offsetY
    x2 = offsetX + daarrt.clawLenght
    y2 = offsetY + daarrt.clawWidthClosed/2
    x3 = offsetX
    y3 = offsetY + daarrt.clawWidthClosed/2
    claw = [(x0,y0),(x1,y1),(x2,y2),(x3,y3)]

    return claw

def createClawBase(daarrt,offsetX,offsetY):

    '''
    return :
        list corresponding to the daarrt's clawBase

    arguments :
        daarrt object
        offsetX : optionnal offset on X axis
        offsetY : optionnal offset on Y axis

    '''

    x11 = offsetX
    y11 = offsetY
    x12 = offsetX + daarrt.clawBase
    y12 = offsetY
    x13 = offsetX + daarrt.clawBase
    y13 = offsetY + daarrt.clawWidthClosed
    x14 = offsetX
    y14 = offsetY + daarrt.clawWidthClosed
    clawBase=[(x11,y11),(x12,y12),(x13,y13),(x14,y14)]

    return clawBase

def createRobot(daarrt):

    '''
    return :
        list pylygon object corresponding to the daarrt (wheel )

    arguments :
        daarrt object

    '''

    rotationCenter = [ -daarrt.robotLenght/2 , -daarrt.robotWidth/2 ]

    body = createBody(daarrt , rotationCenter[0] , rotationCenter[1])
    frontId = createFrontId(daarrt , rotationCenter[0] , rotationCenter[1])

    wheel1 = createWheel(daarrt , -daarrt.wheelLenght/2 + rotationCenter[0] , rotationCenter[1])
    wheel2 = createWheel(daarrt , daarrt.robotLenght - daarrt.wheelLenght/2 + rotationCenter[0] , rotationCenter[1])
    wheel3 = createWheel(daarrt , daarrt.robotLenght - daarrt.wheelLenght/2 + rotationCenter[0] , daarrt.robotWidth + daarrt.wheelWidth + rotationCenter[1])
    wheel4 = createWheel(daarrt , -daarrt.wheelLenght/2 + rotationCenter[0] , daarrt.robotWidth + daarrt.wheelWidth + rotationCenter[1])

    clawBase = createClawBase( daarrt , daarrt.robotLenght + rotationCenter[0] , daarrt.robotWidth/2 - daarrt.clawWidthOpened/2 + rotationCenter[1])
    claw1 = createClaw(daarrt , daarrt.robotLenght + daarrt.clawBase + rotationCenter[0] , daarrt.robotWidth/2 - daarrt.clawWidthClosed/2 - daarrt.clawWidthOpened * daarrt.clawOpening/180.0 + rotationCenter[1])
    claw2 = createClaw(daarrt , daarrt.robotLenght + daarrt.clawBase + rotationCenter[0] , daarrt.robotWidth/2 + daarrt.clawWidthOpened * daarrt.clawOpening/180.0 + rotationCenter[1])

    #robotTmp = [pylygon.Polygon(body) , pylygon.Polygon(clawBase) , pylygon.Polygon(wheel1) , pylygon.Polygon(wheel2) , pylygon.Polygon(wheel3) , pylygon.Polygon(wheel4) , pylygon.Polygon(claw1) , pylygon.Polygon(claw2)]
    #robot = [poly_translate(poly_rotate(element,daarrt.robotCap),daarrt.posX,daarrt.posY) for element in robotTmp]

    robotTmp = [pylygon.Polygon(body) , pylygon.Polygon(frontId) , pylygon.Polygon(wheel1) , pylygon.Polygon(wheel2) , pylygon.Polygon(wheel3) , pylygon.Polygon(wheel4)]
    robot = [poly_translate(poly_rotate(element,daarrt.robotCap),daarrt.posX,daarrt.posY) for element in robotTmp]

    return robot

def createObstacle(world,x,y):

    '''
    return :
        pylygon object corresponding to an obstacle

    arguments :
        x : position on x Axis
        y : position on y Axis

    '''

    obs=pylygon.Polygon([(x,y),(x+world.elementSize,y),(x+world.elementSize,y+world.elementSize),(x,y+world.elementSize)])

    return obs

def createWallOld(world,num_case,num_line):

    '''
    return :
        list of pylygon object corresponding to the walls of a World

    arguments :
        num_case : number of case
        num_line : number of line

    '''

    polyObs1=[(0,0),((num_case) * world.elementSize,0),((num_case) * world.elementSize,world.elementSize),(0,world.elementSize)]
    polyObs2=[(0,world.elementSize),(world.elementSize,world.elementSize),(world.elementSize,(num_line) * world.elementSize),(0,(num_line) * world.elementSize)]
    polyObs3=[((num_case - 1) * world.elementSize,world.elementSize),((num_case) * world.elementSize,world.elementSize),((num_case) * world.elementSize,(num_line - 1) * world.elementSize),(((num_case - 1) * world.elementSize,(num_line - 1) * world.elementSize))]
    polyObs4=[(0,(num_line - 1) * world.elementSize),(num_case * world.elementSize,(num_line - 1) * world.elementSize),(num_case*world.elementSize,num_line * world.elementSize),(0,num_line * world.elementSize)]
    polyObs5=[(18*world.elementSize,0),(19*world.elementSize,0),(19*world.elementSize,12*world.elementSize), (18*world.elementSize,12*world.elementSize)]
    polyObs6=[(31*world.elementSize,11*world.elementSize),(32*world.elementSize,11*world.elementSize), (32*world.elementSize,(num_line-1)*world.elementSize), (31*world.elementSize,(num_line-1)*world.elementSize)]
              
    walls=[pylygon.Polygon(polyObs1),pylygon.Polygon(polyObs2),pylygon.Polygon(polyObs3),pylygon.Polygon(polyObs4)]
    walls=[pylygon.Polygon(polyObs1),pylygon.Polygon(polyObs2),pylygon.Polygon(polyObs3),pylygon.Polygon(polyObs4),pylygon.Polygon(polyObs5),pylygon.Polygon(polyObs6)]

    return walls

def elementWall(ix0,iy0,ix1,iy1,elementSize):
    polyObs=[(ix0*elementSize,iy0*elementSize),(ix1*elementSize,iy0*elementSize),(ix1*elementSize,iy1*elementSize),(ix0*elementSize,iy1*elementSize)]
    #print polyObs
    ply = pylygon.Polygon(polyObs)
    #print ply
    return ply


def createWallOld1(world,num_case,num_line):

    '''
    return :
        list of pylygon object corresponding to the walls of a World

    arguments :
        num_case : number of case
        num_line : number of line

    '''
    
    walls=[]
    elsz=world.elementSize
    walls.append(elementWall(0,0,num_case,1,elsz))
    walls.append(elementWall(0,0,1,num_line,elsz))
    walls.append(elementWall(num_case-1,0,num_case,num_line,elsz))
    walls.append(elementWall(0,num_line-1,num_case,num_line,elsz))
    walls.append(elementWall(num_case/5,0,1+num_case/5,num_line/2,elsz))
    walls.append(elementWall(3*num_case/5,0,1+3*num_case/5,num_line/2,elsz))

    walls.append(elementWall(int(0.5*num_case/5.),int(0.25*num_line),1+int(0.5*num_case/5.0),int(0.75*num_line),elsz))
    walls.append(elementWall(int(2.5*num_case/5.),int(0.25*num_line),1+int(2.5*num_case/5.0),int(0.75*num_line),elsz))
    walls.append(elementWall(int(0.5*num_case/5.),int(0.75*num_line),1+int(4.5*num_case/5.0),1+int(0.75*num_line),elsz))


    walls.append(elementWall(int(3.75*num_case/5.),int(0.25*num_line),1+int(4.25*num_case/5.0),1+int(0.45*num_line),elsz))
   
    return walls

def createWall(world,num_case,num_line):

    '''
    return :
        list of pylygon object corresponding to the walls of a World

    arguments :
        num_case : number of case
        num_line : number of line

    '''
    
    walls=[]
    elsz=world.elementSize
    walls.append(elementWall(0,0,num_case,1,elsz))
    walls.append(elementWall(0,0,1,num_line,elsz))
    walls.append(elementWall(num_case-1,0,num_case,num_line,elsz))
    walls.append(elementWall(0,num_line-1,num_case,num_line,elsz))
    
    walls.append(elementWall(num_case/5,0,1+num_case/5,num_line/3,elsz))
    walls.append(elementWall(3*num_case/5,0,1+3*num_case/5,num_line/3,elsz))

    walls.append(elementWall(int(0.5*num_case/5.),int(0.33*num_line),1+int(0.5*num_case/5.0),int(0.67*num_line),elsz))
    walls.append(elementWall(int(2.5*num_case/5.),int(0.33*num_line),1+int(2.5*num_case/5.0),int(0.67*num_line),elsz))
    #walls.append(elementWall(int(0.5*num_case/5.),int(0.67*num_line),1+int(4.5*num_case/5.0),1+int(0.67*num_line),elsz))
    walls.append(elementWall(int(0.5*num_case/5.),int(0.67*num_line),1+int(4.2*num_case/5.0),1+int(0.67*num_line),elsz))


    walls.append(elementWall(int(3.6*num_case/5.),int(0.2*num_line),1+int(4.5*num_case/5.0),1+int(0.50*num_line),elsz))
   
    return walls



def poly_translate (p, tx, ty):

    '''
    return :
        pylygon object corresponding to the argument translated

    arguments :
        p  : pylygon object to translate
        tx : translation on X axis
        ty : translation on Y axis

    '''

    points = p.P
    pointsTranslates = array([(x+tx,y+ty) for (x,y) in points])
    p.P = pointsTranslates

    return pylygon.Polygon(p)

def poly_rotate (p, theta):

    '''
    return :
        pylygon object corresponding to the argument rotated

    arguments :
        p  : pylygon object to rotate
        theta : rotation angle in degrees

    '''

    theta=theta * math.pi/180.0
    points=p.P
    pointsTournes = array([(x * math.cos(theta)-y * math.sin(theta),
                  x * math.sin(theta) + y * math.cos(theta)) for (x,y) in points])
    p.P=pointsTournes

    return pylygon.Polygon(p)


# some new functions for sonar intersection
def findVertexinPoly(ply,pt):
    iOk=-1
    i=0
    for ptp in ply.P:
        if (ptp[0]==pt[0]) and (ptp[1]==pt[1]):
            iOk=1
            break
        i+=1
    if iOk==1:
        return i
    else:
        return iOk


def line_intersect(p0, p1, m0=None, m1=None, q0=None, q1=None):
    ''' intersect 2 lines given 2 points and (either associated slopes or one extra point)
    Inputs:
        p0 - first point of first line [x,y]
        p1 - fist point of second line [x,y]
        m0 - slope of first line
        m1 - slope of second line
        q0 - second point of first line [x,y]
        q1 - second point of second line [x,y]
    '''
    if m0 is  None:
        if q0 is None:
            raise ValueError('either m0 or q0 is needed')
        dy = q0[1] - p0[1]
        dx = q0[0] - p0[0]
        #print "1", dx,dy
        lhs0 = [-dy, dx]
        rhs0 = p0[1] * dx - dy * p0[0]
    else:
        lhs0 = [-m0, 1]
        rhs0 = p0[1] - m0 * p0[0]

    if m1 is  None:
        if q1 is None:
            raise ValueError('either m1 or q1 is needed')
        dy = q1[1] - p1[1]
        dx = q1[0] - p1[0]
        #print "2",dx,dy
        lhs1 = [-dy, dx]
        rhs1 = p1[1] * dx - dy * p1[0]
    else:
        lhs1 = [-m1, 1]
        rhs1 = p1[1] - m1 * p1[0]

    a = array([lhs0, 
                  lhs1])

    b = array([rhs0, 
                  rhs1])
    try:
        px = linalg.solve(a, b)
    except:
        px = array([nan, nan])
        px = None

    return px
        
def intersectpoly (poly, other, sonarLoc):
    xs0,ys0 = sonarLoc
    intersect = False
    xit=None
    yit=None
    dist=None
    if poly.collidepoly(other) is False:
        pass
    else:
        x0,y0 = other.P[0]
        for oedge in other.edges:
            x1 = x0-oedge[0]
            y1 = y0-oedge[1]
            #print "o ",x0,y0,x1,y1
            #lobst=pylygon.Line(((x0,y0),(x1,y1)))
            xp0,yp0 = poly.P[0]
            for pedge in poly.edges:
                xp1 = xp0-pedge[0]
                yp1 = yp0-pedge[1]
                #print "p ",xp0,yp0,xp1,yp1
                #lson=pylygon.Line(((xp0,yp0),(xp1,yp1)))
                #print lobst.intersection( ( (xp0,yp0),(xp1,yp1) ) )
                p0=[x0,y0]
                q0=[x1,y1]
                q1=[xp0,yp0]
                p1=[xp1,yp1]
                xyi = line_intersect(p0, p1, q0=q0, q1=q1)
                if xyi is None:
                    pass
                else:
                    xi,yi = xyi                    
                    inside=True
                    if (x1 >= x0):
                        if (xi > x1) or (xi < x0):
                            inside=False
                    else:
                        if (xi > x0) or (xi < x1):
                            inside=False
                    if (y1 >= y0):
                        if (yi > y1) or (yi < y0):
                            inside=False
                    else:
                        if (yi > y0) or (yi < y1):
                            inside=False
                    if inside:
                        di = math.sqrt((xi-xs0)**2.0+(yi-ys0)**2.0)
                        if dist is None:
                            dist=di
                            xit=xi
                            yit=yi
                            intersect=True
                        else:
                            if di < dist:
                                dist=di
                                xit=xi
                                yit=yi                              
                        #print xi,yi,di
                        #print x0,xi,x1,y0,yi,y1
                xp0=xp1
                yp0=yp1
            x0=x1
            y0=y1

        if intersect is False:
            x0,y0 = other.P[0]
            i0=poly.collidepoint((x0,y0))
            if i0 != 0:
                if dist is None:
                    dist=math.sqrt((x0-xs0)**2.0+(y0-ys0)**2.0)
                    xit=x0
                    yit=y0
                    intersect=True
                else:
                    di=math.sqrt((x0-xs0)**2.0+(y0-ys0)**2.0)
                    if di < dist:
                        dist=di
                        xit=x0
                        yit=y0                              
            for oedge in other.edges:
                x1 = x0-oedge[0]
                y1 = y0-oedge[1]
                i1=poly.collidepoint((x1,y1))
                if i1 != 0:
                    if dist is None:
                        dist=math.sqrt((x1-xs0)**2.0+(y1-ys0)**2.0)
                        xit=x1
                        yit=y1
                        intersect=True
                        #print xit,yit,dist
                    else:
                        di=math.sqrt((x1-xs0)**2.0+(y1-ys0)**2.0)
                        if di < dist:
                            dist=di
                            xit=x1
                            yit=y1                              
                            #print xit,yit,dist
                x0=x1
                y0=y1
                
    return intersect,xit,yit,dist                
            
