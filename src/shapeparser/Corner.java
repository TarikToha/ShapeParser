/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package shapeparser;

import java.util.ArrayList;
import java.util.HashSet;


/**
 *
 * @author kazi
 * Corner is special type of Point which has an area associated with it.
 * The area indicated the size of the road junction. Also it has an adjacent 
 * list to indicate other corners adjacent to this corner
 */
public class Corner extends Point {
    
    int id;
    double area,r;
    HashSet< Integer >adjacent;
    ArrayList< Integer >linkId;
    
    public Corner(int _id, double _x, double _y, double _area) {
        super(_x, _y);
        id = _id;
        area = _area;
        r= Math.sqrt(area/Math.acos(-1));
        adjacent = new HashSet<>();
        linkId = new ArrayList<>();
    }
    
}
