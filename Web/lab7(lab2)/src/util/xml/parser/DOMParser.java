package util.xml.parser;

import exception.ParserException;
import model.medicine.Medicine;
import model.medicine.internal.ColorEnum;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;
import util.pharmacy.builder.MedicineBuilder;
import util.pharmacy.director.MedicineDirector;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import java.io.File;
import java.io.IOException;
import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;
import java.util.Locale;


/**
 * DOM parser of XML
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */

public class DOMParser implements MedicinesParser {

    private static final Logger logger = LogManager.getLogger("Parser");

    /**
     * Parse XML file to collective using DOM parser
     *
     * @param fileName name of the file that contains medicines stored in XML format
     * @return parsed medicines list
     * @throws ParserException if some error occurred while parsing XML file
     */
    @Override
    public List<Medicine> parse(String fileName) throws ParserException {
        logger.info("Starting DOM parsing");
        List<Medicine> medicines = new ArrayList<>();
        MedicineDirector director = new MedicineDirector();
        MedicineBuilder builder = new MedicineBuilder();

        File inputFile = new File(fileName);
        DocumentBuilderFactory dbFactory = DocumentBuilderFactory.newInstance();
        DocumentBuilder dBuilder = null;
        Document doc = null;
        try {
            dBuilder = dbFactory.newDocumentBuilder();
            doc = dBuilder.parse(inputFile);
        } catch (SAXException | IOException | ParserConfigurationException e) {
            throw new ParserException("Configuration DOM parser error", e);
        }
        doc.getDocumentElement().normalize();


        NodeList ointmentNodes = doc.getElementsByTagName("ointment");
        NodeList antibioticNodes = doc.getElementsByTagName("antibiotic");
        NodeList gellNodes = doc.getElementsByTagName("gell");
        NodeList pilltNodes = doc.getElementsByTagName("pill");
        NodeList syrupNodes = doc.getElementsByTagName("syrup");


        for (int i = 0; i < ointmentNodes.getLength(); ++i) {
            Node node = ointmentNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                double price = Double.parseDouble(element.getElementsByTagName("price").item(0).getTextContent());
                Date manufactureDate = null;
                try {
                    manufactureDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(element.getElementsByTagName("manufactureDate").item(0).getTextContent());
                } catch (ParseException e) {
                    throw new ParserException("manufactureDate parse error", e);
                }
                Date expirationDate = null;
                try {
                    expirationDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(element.getElementsByTagName("expirationDate").item(0).getTextContent());
                } catch (ParseException e) {
                    throw new ParserException("expirationDate parse error", e);
                }
                boolean isWarming = Boolean.parseBoolean(element.getElementsByTagName("isWarming").item(0).getTextContent());
                double fluidityPercent = Double.parseDouble(element.getElementsByTagName("fluidityPercent").item(0).getTextContent());


                medicines.add(director.manufactureOintment(builder,
                        name,
                        price,
                        manufactureDate,
                        expirationDate,
                        fluidityPercent,
                        isWarming));
                builder.reset();
            }
        }

        for (int i = 0; i < antibioticNodes.getLength(); ++i) {
            Node node = antibioticNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                double price = Double.parseDouble(element.getElementsByTagName("price").item(0).getTextContent());
                Date manufactureDate = null;
                try {
                    manufactureDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(element.getElementsByTagName("manufactureDate").item(0).getTextContent());
                } catch (ParseException e) {
                    throw new ParserException("manufactureDate parse error", e);
                }
                Date expirationDate = null;
                try {
                    expirationDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(element.getElementsByTagName("expirationDate").item(0).getTextContent());
                } catch (ParseException e) {
                    throw new ParserException("expirationDate parse error", e);
                }
                boolean isRecipeRequired = Boolean.parseBoolean(element.getElementsByTagName("isRecipeRequired").item(0).getTextContent());
                double maxDailyDoseInMg = Double.parseDouble(element.getElementsByTagName("maxDailyDoseInMg").item(0).getTextContent());


                medicines.add(director.manufactureAntibiotic(builder,
                        name,
                        price,
                        manufactureDate,
                        expirationDate,
                        maxDailyDoseInMg,
                        isRecipeRequired));
                builder.reset();
            }
        }

        for (int i = 0; i < gellNodes.getLength(); ++i) {
            Node node = gellNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                double price = Double.parseDouble(element.getElementsByTagName("price").item(0).getTextContent());
                Date manufactureDate = null;
                try {
                    manufactureDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(element.getElementsByTagName("manufactureDate").item(0).getTextContent());
                } catch (ParseException e) {
                    throw new ParserException("manufactureDate parse error", e);
                }
                Date expirationDate = null;
                try {
                    expirationDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(element.getElementsByTagName("expirationDate").item(0).getTextContent());
                } catch (ParseException e) {
                    throw new ParserException("expirationDate parse error", e);
                }
                boolean isCooling = Boolean.parseBoolean(element.getElementsByTagName("isCooling").item(0).getTextContent());
                double fluidityPercent = Double.parseDouble(element.getElementsByTagName("fluidityPercent").item(0).getTextContent());


                medicines.add(director.manufactureGell(builder,
                        name,
                        price,
                        manufactureDate,
                        expirationDate,
                        fluidityPercent,
                        isCooling));
                builder.reset();
            }
        }

        for (int i = 0; i < pilltNodes.getLength(); ++i) {
            Node node = pilltNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                double price = Double.parseDouble(element.getElementsByTagName("price").item(0).getTextContent());
                Date manufactureDate = null;
                try {
                    manufactureDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(element.getElementsByTagName("manufactureDate").item(0).getTextContent());
                } catch (ParseException e) {
                    throw new ParserException("manufactureDate parse error", e);
                }
                Date expirationDate = null;
                try {
                    expirationDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(element.getElementsByTagName("expirationDate").item(0).getTextContent());
                } catch (ParseException e) {
                    throw new ParserException("expirationDate parse error", e);
                }
                int doseInMg = Integer.parseInt(element.getElementsByTagName("doseInMg").item(0).getTextContent());
                double maxDailyDoseInMg = Double.parseDouble(element.getElementsByTagName("maxDailyDoseInMg").item(0).getTextContent());


                medicines.add(director.manufacturePill(builder,
                        name,
                        price,
                        manufactureDate,
                        expirationDate,
                        maxDailyDoseInMg,
                        doseInMg));
                builder.reset();
            }
        }

        for (int i = 0; i < syrupNodes.getLength(); ++i) {
            Node node = syrupNodes.item(i);
            if (node.getNodeType() == Node.ELEMENT_NODE) {
                Element element = (Element) node;

                String name = element.getElementsByTagName("name").item(0).getTextContent();
                double price = Double.parseDouble(element.getElementsByTagName("price").item(0).getTextContent());
                Date manufactureDate = null;
                try {
                    manufactureDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(element.getElementsByTagName("manufactureDate").item(0).getTextContent());
                } catch (ParseException e) {
                    throw new ParserException("manufactureDate parse error", e);
                }
                Date expirationDate = null;
                try {
                    expirationDate = new SimpleDateFormat("yyyy-MM-dd", Locale.US).parse(element.getElementsByTagName("expirationDate").item(0).getTextContent());
                } catch (ParseException e) {
                    throw new ParserException("expirationDate parse error", e);
                }
                ColorEnum color = ColorEnum.valueOf(element.getElementsByTagName("color").item(0).getTextContent().toUpperCase());
                double maxDailyDoseInMg = Double.parseDouble(element.getElementsByTagName("maxDailyDoseInMg").item(0).getTextContent());


                medicines.add(director.manufactureSyrup(builder,
                        name,
                        price,
                        manufactureDate,
                        expirationDate,
                        maxDailyDoseInMg,
                        color));
                builder.reset();
            }
        }

        logger.info("Finish DOM parsing");
        return medicines;
    }

}
