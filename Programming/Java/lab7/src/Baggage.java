import java.io.Serializable;
import java.text.DateFormat;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class Baggage implements Serializable  {
    private String  flight_number;
    private Date date;
    private String destination;
    private String full_name;
    private int pieces;
    private double weight;


    public static Baggage read( Scanner fin ){
        //System.out.print( "Flight number: " );
        Baggage baggage = new Baggage();
        DateFormat dateFormat = new SimpleDateFormat("d.mm.yyyy, HH:mm");
        baggage.flight_number = fin.nextLine();
        //System.out.print( "Date: " );
        if ( ! fin.hasNextLine()) return null;
        try {
            baggage.date = dateFormat.parse( fin.nextLine());
        } catch (ParseException e) {
            e.printStackTrace();
        }
        //System.out.print( "Destination: " );
        if ( ! fin.hasNextLine()) return null;
        baggage.destination = fin.nextLine();
        //System.out.print( "Full name: " );
        if ( ! fin.hasNextLine()) return null;
        baggage.full_name = fin.nextLine();
        if ( ! fin.hasNextLine()) return null;
        //System.out.print( "Total picess: " );
        baggage.pieces = Integer.parseInt(fin.nextLine());
        if ( ! fin.hasNextLine()) return null;
        //System.out.print( "Total weight: " );
        baggage.weight = Integer.parseInt( fin.nextLine());
        return baggage;
    }

    public Baggage() {
    }

    public String toString() {
        return String.format("Passeger %s of a flight number %s to %s has %d of baggage, %a kg, %t",full_name,flight_number,destination,pieces,weight, date) ;
    }






}
