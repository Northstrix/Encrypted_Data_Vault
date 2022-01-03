import java.awt.BorderLayout;
import java.io.FileWriter;
import java.io.IOException;
import java.sql.*;
import java.util.Scanner; // Scanner on
import javax.swing.*;


public class DB {
    static JButton crt, add, rem, exp, q;
    static JButton select, cancel, rmv, cncl;
	public static void create_table() {
	      Connection c = null;
	      Statement stmt = null;
	      try {
	         Class.forName("org.sqlite.JDBC");
	         c = DriverManager.getConnection("jdbc:sqlite:records.db");
	         System.out.println("Opened database successfully");

	         stmt = c.createStatement();
	         String sql = "CREATE TABLE RECORDS " +
                     " (NAME      TEXT     NOT NULL, " +
                     " HINT       TEXT     NOT NULL, " + 
                     " IV         TEXT     NOT NULL, " + 
                     " CT         TEXT     NOT NULL, " + 
                     " HASH       TEXT     NOT NULL)"; 
	         stmt.executeUpdate(sql);
	         stmt.close();
	         c.close();
	      } catch ( Exception e ) {
	    	  JFrame f1=new JFrame();  
		      JOptionPane.showMessageDialog(f1, e.getClass().getName() + ": " + e.getMessage() );
	         System.exit(0);
	      }
	      JFrame f1=new JFrame();  
	      JOptionPane.showMessageDialog(f1,"Table created successfully");
	      return;
	}
	
	public static void add_record() {
	      Connection c = null;
	      Statement stmt = null;
	      
	      try {
	    	 String name = JOptionPane.showInputDialog("Enter the name of the record");
	    	 String hint = JOptionPane.showInputDialog("Enter the hint for the master password\nDon't enter the master password itself!");
	    	 String iv = JOptionPane.showInputDialog("Paste the encrypted IV");
	    	 String ct = JOptionPane.showInputDialog("Paste the ciphertext");
	    	 String hash = JOptionPane.showInputDialog("Paste the encrypted hash");
	         Class.forName("org.sqlite.JDBC");
	         c = DriverManager.getConnection("jdbc:sqlite:records.db");
	         c.setAutoCommit(false);
	         stmt = c.createStatement();
	         String sql = "INSERT INTO RECORDS (NAME,HINT,IV,CT,HASH) " +
	                        "VALUES ('"+name+"','"+hint+"', '"+iv+"', '"+ct+"', '"+hash+"' );"; 
	         stmt.executeUpdate(sql);
	         stmt.close();
	         c.commit();
	         c.close();
	      } catch ( Exception e ) {
	    	 JFrame f2=new JFrame();
		     JOptionPane.showMessageDialog(f2, e.getClass().getName() + ": " + e.getMessage() );
	         System.exit(0);
	      }
	      JFrame f2=new JFrame();  
	      JOptionPane.showMessageDialog(f2,"Record created successfully");
	      return;
	}
	
	public static void disp() {
		   Connection c = null;
		   Statement stmt = null;
		   try {
		      Class.forName("org.sqlite.JDBC");
		      c = DriverManager.getConnection("jdbc:sqlite:records.db");
		      c.setAutoCommit(false);
		      stmt = c.createStatement();
		      ResultSet rs = stmt.executeQuery( "SELECT * FROM RECORDS;" );
		      System.out.println("Elements in the database: ");
		      
		      while ( rs.next() ) {
		    	 String  name = rs.getString("name");
		    	 String  hint = rs.getString("hint");
		    	 String  iv = rs.getString("iv");
		    	 String  ct = rs.getString("ct");
		    	 String  hash = rs.getString("hash");
		    	  
		         System.out.println( "name = " + name );
		    	 System.out.println( "hint = " + hint );
		         System.out.println( "iv = " + iv );
		         System.out.println( "ct = " + ct );
		         System.out.println( "hash = " + hash );
		         System.out.println();
		      }
		      rs.close();
		      stmt.close();
		      c.close();
		   } catch ( Exception e ) {
			   JFrame f6=new JFrame();  
			    JOptionPane.showMessageDialog(f6, e.getClass().getName() + ": " + e.getMessage() );
		      System.exit(0);
		   }
		   return;
	}
	
	public static void create_csv() {
		   Connection c = null;
		   Statement stmt = null;
		   try {
		      Class.forName("org.sqlite.JDBC");
		      c = DriverManager.getConnection("jdbc:sqlite:records.db");
		      c.setAutoCommit(false);

		      stmt = c.createStatement();
		      ResultSet rs = stmt.executeQuery( "SELECT * FROM RECORDS;" );
		      try {
				      FileWriter myWriter = new FileWriter("records.csv",false);
				      myWriter.write("");
				      myWriter.close();
					}
					catch (IOException e) {
						JFrame f3=new JFrame();  
					    JOptionPane.showMessageDialog(f3,"Can't create a file for the output data");
					    System.exit(1);
					}
		      writef("Name,Hint for the master password,IV,Ciphertext,Hash");		      
		      while ( rs.next() ) {
		    	  String name = rs.getString("name");
		    	  String hint = rs.getString("hint");
		    	  String iv = rs.getString("iv");
		    	  String ct = rs.getString("ct");
		    	  String hash = rs.getString("hash");
		    	  writef("\n");
		    	  writef(name + ",");
		    	  writef(hint + ",");
		    	  writef(iv + ",");
		    	  writef(ct + ",");
		    	  writef(hash);
		      }
		      rs.close();
		      stmt.close();
		      c.close();
		   } catch ( Exception e ) {
		      System.err.println( e.getClass().getName() + ": " + e.getMessage() );
		      System.exit(0);
		   }
		   return;
	}
	
	
	public static void remove_rec() {
		   Connection c = null;
		   Statement stmt = null;
		   try {
		      Class.forName("org.sqlite.JDBC");
		      c = DriverManager.getConnection("jdbc:sqlite:records.db");
		      c.setAutoCommit(false);
		      stmt = c.createStatement();
		      ResultSet rs = stmt.executeQuery( "SELECT * FROM RECORDS;" );
			  JFrame remrec = new JFrame("Delete record");
		      JMenuBar rm = new JMenuBar();
		      String rcrds[] = new String [1000];
			  JComboBox records = new JComboBox();
		      int n = 0;
		      while (rs.next()) {
		    	 rcrds[n] = (rs.getString("name"));
		    	 n++;
		      }
		      int m = 0;
		      while (rcrds[m] != null) {
		    	 m++;
		      }
		      for(int i = 0; i < m; i++) {
		    	  records.addItem(rcrds[i]);
		      }
		      remrec.setJMenuBar(rm);
			  rm.add(records);
			  rmv = new JButton("Delete");  
		      cncl = new JButton("Cancel");   
		      rm.add(rmv);  
		      rm.add(cncl);  
			 
		      remrec.setSize(400, 65);  
		      remrec.setVisible(true); 
		      rs.close();
		      stmt.close();
		      c.close(); 
			    rmv.addActionListener(e ->
		        {
		        	remove(rcrds[records.getSelectedIndex()]);
		        	remrec.dispose();
	   	
		        });
			    cncl.addActionListener(e ->
		        {
		        	remrec.dispose();
	   	
		        });
		   } catch ( Exception e ) {
			  JFrame f4=new JFrame();  
			  JOptionPane.showMessageDialog(f4, e.getClass().getName() + ": " + e.getMessage() );
		      System.exit(0);
		   }
		   return;
	}

	public static void remove(String name) {
	      Connection c = null;
	      Statement stmt = null;
	      try {
	         Class.forName("org.sqlite.JDBC");
	         c = DriverManager.getConnection("jdbc:sqlite:records.db");
	         c.setAutoCommit(false);

	         stmt = c.createStatement();
	         String sql = "DELETE from RECORDS where NAME='"+name+"';";
	         stmt.executeUpdate(sql);
	         c.commit();

	      c.close();
	      } catch ( Exception e ) {
				JFrame f5=new JFrame();  
			    JOptionPane.showMessageDialog(f5, e.getClass().getName() + ": " + e.getMessage() );
	         System.exit(0);
	      }
	      return;
	}
	
	public static void writef(String s) {
		try {
	      FileWriter myWriter = new FileWriter("records.csv",true);
	      myWriter.write(s);
	      myWriter.close();
		}
		catch (IOException e) {
			JFrame f5=new JFrame();  
		    JOptionPane.showMessageDialog(f5,"Can't create a file for the output data");
		    System. exit(1);
		    }
		return;
	}
	
   public static void main( String args[] ) {
	JFrame f=new JFrame("Database for the data vault");
    crt = new JButton("Create table");
    add = new JButton("Add record");
    rem = new JButton("Delete record");
    exp = new JButton("Export records into .csv file");
    q = new JButton("Quit");
    JPanel p = new JPanel();
    BoxLayout boxLayout = new BoxLayout(p, BoxLayout.Y_AXIS);
    p.setLayout(boxLayout);
    p.add(crt);
    p.add(add);
    p.add(rem);
    p.add(exp);
    p.add(q);
    f.setSize(210,170); 
    f.add(p);
    f.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
    f.setVisible(true);
    f.setLayout(null);
    crt.addActionListener(e ->
    {
    	create_table();
    });
    add.addActionListener(e ->
    {
    	add_record();
    });
    rem.addActionListener(e ->
    {
    	remove_rec();
    });
    exp.addActionListener(e ->
    {
    	create_csv();
    });
    q.addActionListener(e ->
    {
    	System.exit(0);
    });
   }
}