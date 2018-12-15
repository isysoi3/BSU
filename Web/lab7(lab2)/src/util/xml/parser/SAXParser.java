package util.xml.parser;

import exception.ParserException;
import model.medicine.Medicine;
import org.apache.logging.log4j.LogManager;
import org.apache.logging.log4j.Logger;

import java.util.List;

public class SAXParser implements MedicinesParser {

    private static final Logger logger = LogManager.getLogger("Parse");

    /**
     * Parse XML file to collective using SAX parser
     * @param fileName name of the file that contains collective stored in XML format
     * @return parsed collective object
     * @throws ParserException if some error occurred while parsing XML file
     * */
    @Override
    public List<Medicine> parse(String fileName) throws ParserException {
        return null;
    }
}

