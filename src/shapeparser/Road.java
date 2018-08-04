/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shapeparser;

import java.util.ArrayList;

/**
 *
 * @author kazi
 */
public class Road {
    
    int id, cornerId1, cornerId2;
    Point line00, line01, line10, line11, final1, final2;
    double width;
            
    Road(int _id, int id1, int id2, Point c1, Point c2, double w) {
        double theta, x, y;
        Point temp;
        int i;
        id = _id;
        width = w;
        w /= 2;
        theta = Math.atan((c2.y - c1.y)/(c2.x - c1.x));
        y = w*Math.cos(theta);
        x = w*Math.sin(theta);
        line00 = c1.add(new Point(-x,y));
        line01 = c2.add(new Point(-x,y));
        line10 = c1.add(new Point(x,-y));
        line11 = c2.add(new Point(x,-y));
        
        if(line01.minus(line00).cross(c2.minus(line01)) > 0) {
            temp = line00;
            line00 = line01;
            line01 = temp;
            
            temp = line10;
            line10 = line11;
            line11 = temp;
            
            i = id1;
            id1 = id2;
            id2 = i;
        }
        cornerId1 = id1;
        cornerId2 = id2;
    }
    
    void Show() {
        System.out.println("Showing\n");
        line00.Show();
        line01.Show();
        line10.Show();
        line11.Show();
    }
    
    String Show2() {
        return id + "," + line00.x + "," + line00.y + "\n" + id + "," + line01.x + "," + line01.y + "\n";
    }
}
