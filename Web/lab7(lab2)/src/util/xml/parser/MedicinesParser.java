package util.xml.parser;

import exception.ParserException;
import model.medicine.Medicine;
import java.util.List;

/**
 * Parsing interface
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */

public interface MedicinesParser {
    List<Medicine> parse(String fileName) throws ParserException;
}
