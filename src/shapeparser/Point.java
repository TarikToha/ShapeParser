/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shapeparser;

import static java.lang.Math.sqrt;
import java.util.ArrayList;

/**
 *
 * @author kazi
 */
public class Point {

    double x, y;

    public Point(double _x, double _y) {
        x = _x;
        y = _y;
    }

    Point(Point p) {
        x = p.x;
        y = p.y;
    }

    Point add(Point p) {
        Point ret = new Point(x + p.x, y + p.y);
        return ret;
    }

    Point minus(Point p) {
        Point ret = new Point(x - p.x, y - p.y);
        return ret;
    }

    Point mult(double c) {
        Point ret = new Point(x * c, y * c);
        return ret;
    }

    double dot(Point p) {
        return x * p.x + y * p.y;
    }

    double cross(Point p) {
        return x * p.y - y * p.x;
    }

    double magnitude() {
        return sqrt(x * x + y * y);
    }

    void Show() {
        System.out.println("(" + x + ", " + y + ")\n");
    }

    Point scaledP(double s) {
        Point ret = new Point((s * x) / this.magnitude(), (s * y) / this.magnitude());
        return ret;
    }

    double distFrom(Point p) {
        Point temp = this.minus(p);
        return temp.magnitude();
    }

    /*
    * poly is a polygon represented by an array of points. The function returns
    * true if the point is inside the polygon
     */
    boolean isInside(ArrayList<Point> poly, double xMin, double xMax, double yMin, double yMax) {
        boolean c = false;
        if (this.x < xMin || this.x > xMax || this.y < yMin || this.y > yMax) {
            return false;
        }
        for (int i = 0; i < poly.size(); i++) {
            int j = (i + 1) % poly.size();
            if ((poly.get(i).y <= this.y && this.y < poly.get(j).y
                    || poly.get(j).y <= this.y && this.y < poly.get(i).y)
                    && this.x < poly.get(i).x
                    + (poly.get(j).x - poly.get(i).x) * (this.y - poly.get(i).y) / (poly.get(j).y - poly.get(i).y)) {
                c = !c;
            }
        }
        return c;
    }

    /**
     * *For hashing*
     */
    @Override
    public boolean equals(Object o) {
        Point p = (Point) o;
        return this.x == p.x && this.y == p.y;
    }

    @Override
    public int hashCode() {
        return (int) (this.x * 1000 + this.y);
    }

    @Override
    public String toString() {
        return x + ", " + y + ";";
    }

}
