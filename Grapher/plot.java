import java.awt.*;
import java.awt.event.*;
import java.awt.geom.*;
import javax.swing.*;
import java.io.*;
import java.util.Scanner;

class plot extends JFrame{
	plot(String fNm){
		JFrame f = new JFrame();
		f.setTitle("Graph");
		f.setSize(501,501);
		f.setDefaultCloseOperation(EXIT_ON_CLOSE);
		f.setVisible(true);

		draw d = new draw(fNm);
		f.add(d);
	}
	public static void main(String[] args){
		new plot(args[0]);
//		System.out.println(args[0]);
	}
}

class draw extends JPanel{
	String fNm;
	draw(String f){
		fNm = f;
	}
	public void paintComponent(Graphics g){

//	...Primary Axis XX', YY'
		g.setColor(Color.RED);
		g.drawLine(0,250,500,250);
		g.drawLine(250,0,250,500);

//	... Points
		g.setColor(Color.BLUE);
		try{
			File f = new File(fNm);
			Scanner s = new Scanner(f);
			while(s.hasNext()){
//				if(s.hasNextInt()){
					int x = s.nextInt();
					int y = s.nextInt();
	
					g.drawLine(x,y,x,y);			// ...Puts Point
//					System.out.println(x+" "+y);
//				}
//				else
//					s.next();
			}
		}catch(Exception e){}

	}
}
