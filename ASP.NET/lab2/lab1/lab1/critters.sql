-- MySQL dump 10.16  Distrib 10.1.26-MariaDB, for debian-linux-gnu (x86_64)
--
-- Host: localhost    Database: db
-- ------------------------------------------------------
-- Server version	10.1.26-MariaDB-0+deb9u1

/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;
/*!40103 SET @OLD_TIME_ZONE=@@TIME_ZONE */;
/*!40103 SET TIME_ZONE='+00:00' */;
/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;

--
-- Table structure for table `roster`
--

DROP TABLE IF EXISTS `roster`;
/*!40101 SET @saved_cs_client     = @@character_set_client */;
/*!40101 SET character_set_client = utf8 */;
CREATE TABLE `roster` (
  `playerid` varchar(8) DEFAULT NULL,
  `jersey` int(11) DEFAULT NULL,
  `fname` varchar(8) DEFAULT NULL,
  `sname` varchar(9) DEFAULT NULL,
  `position` varchar(2) DEFAULT NULL,
  `birthday` varchar(19) DEFAULT NULL,
  `weight` int(11) DEFAULT NULL,
  `height` int(11) DEFAULT NULL,
  `birthcity` varchar(11) DEFAULT NULL,
  `birthstate` varchar(2) DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;
/*!40101 SET character_set_client = @saved_cs_client */;

--
-- Dumping data for table `roster`
--

LOCK TABLES `roster` WRITE;
/*!40000 ALTER TABLE `roster` DISABLE KEYS */;
INSERT INTO `roster` VALUES ('adamlem',12,'Mike','Adamle','RW','1985-09-21 00:00:00',73,197,'Stamford','CT'),('armanova',31,'Arkady','Armanov','LW','1998-10-25 00:00:00',71,197,'Minsk','RU'),('choakd',11,'Dominick','Choak','RW','1997-02-22 00:00:00',72,196,'Prague','CZ'),('clubbes',7,'Sam','Clubbe','LW','1999-07-26 00:00:00',75,190,'Paramus','NJ'),('fiskj',25,'Jerke','Fisk','D','1985-11-25 00:00:00',71,193,'Helsinki','FI'),('grunwala',6,'Allan','Grunwald','C','1990-10-17 00:00:00',74,189,'Buffalo','NY'),('jeffriea',30,'Angus','Jeffries','G','1995-11-08 00:00:00',70,185,'Springfield','MA'),('lexourb',9,'Bruce','Lexour','D','1988-09-05 00:00:00',75,198,'Quincy','IL'),('maguirea',34,'Andre','Maguire','LW','1999-12-08 00:00:00',75,191,'Detroit','MI'),('olsens',37,'Sandish','Olsen','D','1999-08-16 00:00:00',72,192,'Stockholm','SW'),('springej',38,'Junior','Springer','C','1995-10-14 00:00:00',71,184,'Toronto','ON'),('travisj',19,'John','Travis','C','1985-06-23 00:00:00',74,200,'Boston','MA');
/*!40000 ALTER TABLE `roster` ENABLE KEYS */;
UNLOCK TABLES;
/*!40103 SET TIME_ZONE=@OLD_TIME_ZONE */;

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;

-- Dump completed on 2018-09-08 22:53:52
