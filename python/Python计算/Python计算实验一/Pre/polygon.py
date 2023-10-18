"""This module contains code from
Think Python by Allen B. Downey
http://thinkpython.com

Copyright 2012 Allen B. Downey
License: GNU GPLv3 http://www.gnu.org/licenses/gpl.html

"""

import math

try:
    # see if Swampy is installed as a package
    from swampy.TurtleWorld import *
except ImportError:
    # otherwise see if the modules are on the PYTHONPATH
    from TurtleWorld import *


def square(t, length):
    """Draws a square with sides of the given length.

    Returns the Turtle to the starting position and location.
    """
    for i in range(4):
        fd(t, length)
        lt(t)


def polyline(t, n, length, angle):
    """Draws n line segments.

    t: Turtle object
    n: number of line segments
    length: length of each segment
    angle: degrees between segments
    """
    for i in range(n):
        fd(t, length)
        lt(t, angle)


def polygon(t, n, length):
    """Draws a polygon with n sides.

    t: Turtle
    n: number of sides
    length: length of each side.
    """
    angle = 360.0/n
    polyline(t, n, length, angle)


def arc(t, r, angle):
    """Draws an arc with the given radius and angle.

    t: Turtle
    r: radius
    angle: angle subtended by the arc, in degrees
    """
    arc_length = 2 * math.pi * r * abs(angle) / 360
    n = int(arc_length / 4) + 1
    step_length = arc_length / n
    step_angle = float(angle) / n

    # making a slight left turn before starting reduces
    # the error caused by the linear approximation of the arc
    lt(t, step_angle/2)
    polyline(t, n, step_length, step_angle)
    rt(t, step_angle/2)


def circle(t, r):
    """Draws a circle with the given radius.

    t: Turtle
    r: radius
    """
    arc(t, r, 360)


# the following condition checks whether we are
# running as a script, in which case run the test code,
# or being imported, in which case don't.

if __name__ == '__main__':
    world = TurtleWorld()    
    bob = Turtle()
    radius = 100

    #验证正多边形边长相同时，边数越多面积越大
    rt(bob)                             #调整角度
    pd(bob)
    bob.delay=0.1                       #改变间隔时间
    for i in range(12):
        polygon(bob,i+3,radius)
    
    #验证圆的内接正多边形边数越多越接近圆
    pu(bob)                             #提笔
    fd(bob,0.5*radius)                  #调整合适的位置
    lt(bob)
    fd(bob,7*radius)
    rt(bob)
    pd(bob)                             #落笔
    bob.delay=0.001
    set_color(bob,'violet')             #改变乌龟颜色为紫罗兰色
    circle(bob,2*radius)                #画圆
    
    bob.delay=0.1
    for i in range(12):
        angle1=180.0/(i+3)              #每次画圆内接多边形需要转过的角度
        lt(bob,angle1)
        polygon(bob,i+3,4*radius*(math.sin(math.pi/(i+3))))
        rt(bob,angle1)                  #因为polygon默认会转过一个角度，所以要补齐到垂直

    #花瓣
    pu(bob)                             #提笔
    fd(bob,1.5*radius)                  #调至合适位置
    rt(bob)
    fd(bob,0.75*radius)
    pd(bob)                             #落笔
    set_pen_color(bob,'red')            #笔的颜色设为红色
    for i in range(5):                  #花花瓣
        polygon(bob,i+3,radius)
    
    #花茎
    pu(bob)                             #提笔
    fd(bob,0.5*radius)                  #调至合适的位置
    lt(bob)
    fd(bob,2.2*radius)
    pd(bob)                             #落笔
    set_pen_color(bob,'green')          #笔的颜色设为绿色
    fd(bob,2*radius)                    #画花茎

    #花叶左
    bk(bob,1.3*radius)
    rt(bob,60)
    fd(bob,0.7*radius)
    rt(bob,60)
    fd(bob,0.7*radius)
    rt(bob,120)
    fd(bob,0.7*radius)
    rt(bob,60)
    fd(bob,0.7*radius)
    
    #花叶右
    rt(bob,60)
    fd(bob,0.4*radius)
    lt(bob,60)
    fd(bob,0.7*radius)
    lt(bob,60)
    fd(bob,0.7*radius)
    lt(bob,120)
    fd(bob,0.7*radius)
    lt(bob,60)
    fd(bob,0.7*radius)

    bob.die()
    wait_for_user()
