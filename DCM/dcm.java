import java.awt.*;
import javax.swing.*;
public class dcm extends JFrame{
	private Container c;
	private JPanel pnl;
	private Point p;
	private int x, y, r, g, b;
	private JTextField xT, yT, rT, gT, bT;
	private Robot rob;
	private Color col;

	dcm(){
		setTitle("Digital Color Meter");
		setBounds(100,100,300,100);
		setDefaultCloseOperation(EXIT_ON_CLOSE);
		setVisible(true);

		c = this.getContentPane();
		c.setLayout(null);
		c.setBackground(Color.GREEN);

		pnl = new JPanel();
		pnl.setBounds(25,25,50,50);
		add(pnl);

		xT = new JTextField();
		xT.setBounds(100, 25, 50, 20);
		xT.setEditable(false);
		add(xT);		

		yT = new JTextField();
		yT.setBounds(200, 25, 50, 20);
		yT.setEditable(false);
		add(yT);		

		rT = new JTextField();
		rT.setBounds(100, 50, 50, 20);
		rT.setEditable(false);
		add(rT);		

		gT = new JTextField();
		gT.setBounds(150, 50, 50, 20);
		gT.setEditable(false);
		add(gT);		

		bT = new JTextField();
		bT.setBounds(200, 50, 50, 20);
		bT.setEditable(false);
		add(bT);		

		try{
			rob = new Robot();
		}catch(Exception e){}
		while(true){
			p = MouseInfo.getPointerInfo().getLocation();
			x = p.x;
			y = p.y;
			try{
				col = rob.getPixelColor(x, y);
				xT.setText(Integer.toString(x));
				yT.setText(Integer.toString(y));
				r = col.getRed();
				g = col.getGreen();
				b = col.getBlue();
				rT.setText(Integer.toString(r));
				gT.setText(Integer.toString(g));
				bT.setText(Integer.toString(b));
				pnl.setBackground(new java.awt.Color(r, g, b));
			}catch(Exception e){}
		}
	}
	public static void main(String[] args){
		new dcm();
	}
}
