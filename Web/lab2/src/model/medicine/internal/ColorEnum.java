package model.medicine.internal;

/**
 * enum that represent colors
 *
 * @author Ilya Sysoi
 * @version 1.0.0
 */
public enum ColorEnum {
    RED {
        public String toString() {
            return "red";
        }
    },
    GREEN {
        public String toString() {
            return "green";
        }
    },
    YELLOW {
        public String toString() {
            return "yellow";
        }
    }
}