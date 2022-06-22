-- phpMyAdmin SQL Dump
-- version 5.0.3
-- https://www.phpmyadmin.net/
--
-- Host: 127.0.0.1
-- Generation Time: Jun 22, 2022 at 08:56 PM
-- Server version: 10.4.14-MariaDB
-- PHP Version: 7.4.11

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- Database: `voting_system`
--

-- --------------------------------------------------------

--
-- Table structure for table `admin`
--

CREATE TABLE `admin` (
  `name` varchar(30) NOT NULL,
  `admin_id` int(8) NOT NULL,
  `constituency` varchar(30) NOT NULL,
  `password_hash` varchar(128) NOT NULL,
  `event_id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `admin`
--

INSERT INTO `admin` (`name`, `admin_id`, `constituency`, `password_hash`, `event_id`) VALUES
('Vinyas Kulal', 123456, 'India', 'fbde9cc9a5b73ff6e2800960c5bd9d4f', 0);

-- --------------------------------------------------------

--
-- Table structure for table `candidate`
--

CREATE TABLE `candidate` (
  `candidate_id` int(11) NOT NULL,
  `name` varchar(30) NOT NULL,
  `constituency` varchar(30) NOT NULL,
  `dob` date NOT NULL,
  `nationality` varchar(20) NOT NULL,
  `aadhar_id` bigint(12) NOT NULL,
  `party` varchar(30) NOT NULL,
  `voter_id` bigint(12) NOT NULL,
  `img_url` text NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `candidate`
--

INSERT INTO `candidate` (`candidate_id`, `name`, `constituency`, `dob`, `nationality`, `aadhar_id`, `party`, `voter_id`, `img_url`) VALUES
(8953, 'Brendan Lucas', 'Lower Parel', '2001-05-01', 'Indian', 856246321539, 'AAP', 19702291819, 'https://www.ndtv.com/india-news/aap-logo-designer-sereves-legal-notice-on-arvind-kejriwal-775881'),
(8944, 'Abhi Gupta', 'Andheri', '2001-07-06', 'Indian', 942184516165, 'INC', 67039242891, 'https://assets.sentinelassam.com/h-upload/2020/07/01/140759-congress-logo.webp?w=940&dpr=1.3'),
(8958, 'Dhananjay Nair', 'Kharghar', '1998-04-01', 'Indian', 451926591265, 'BJP', 48779115226, 'https://1000logos.net/wp-content/uploads/2022/02/BJP-logo.png');

-- --------------------------------------------------------

--
-- Table structure for table `result`
--

CREATE TABLE `result` (
  `candidate_id` int(11) NOT NULL,
  `event_id` int(11) NOT NULL,
  `no_of_votes` int(11) NOT NULL,
  `result` varchar(10) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

-- --------------------------------------------------------

--
-- Table structure for table `users`
--

CREATE TABLE `users` (
  `name` varchar(30) NOT NULL,
  `voter_id` bigint(12) NOT NULL,
  `constituency` varchar(20) NOT NULL,
  `dob` date NOT NULL,
  `aadhar_id` bigint(12) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `users`
--

INSERT INTO `users` (`name`, `voter_id`, `constituency`, `dob`, `aadhar_id`) VALUES
('Aditya mahamuni', 159167113040, 'Wadala', '2001-04-01', 446146343220),
('Brendan Lucas', 159867239832, 'Worli', '2001-05-01', 459115037991),
('Jayesh Badwal', 159967921427, 'Malad', '2000-09-15', 123465789012);

-- --------------------------------------------------------

--
-- Table structure for table `voting`
--

CREATE TABLE `voting` (
  `event_id` int(11) NOT NULL,
  `voter_id` bigint(12) NOT NULL,
  `vote` bigint(11) NOT NULL,
  `Timestamp` timestamp NOT NULL DEFAULT current_timestamp()
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `voting`
--

INSERT INTO `voting` (`event_id`, `voter_id`, `vote`, `Timestamp`) VALUES
(789456, 953449880, 2, '2022-06-19 14:15:19'),
(789456, 159167113040, 0, '2022-06-21 07:27:02'),
(789456, 159967921427, 0, '2022-06-13 07:26:12');

-- --------------------------------------------------------

--
-- Table structure for table `voting_event`
--

CREATE TABLE `voting_event` (
  `event_id` int(11) NOT NULL,
  `status` varchar(10) NOT NULL,
  `no_of_voters` int(11) NOT NULL,
  `start_date` date NOT NULL,
  `end_date` date NOT NULL,
  `no_of_candidates` int(11) NOT NULL,
  `constituency` varchar(20) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

--
-- Dumping data for table `voting_event`
--

INSERT INTO `voting_event` (`event_id`, `status`, `no_of_voters`, `start_date`, `end_date`, `no_of_candidates`, `constituency`) VALUES
(789456, 'pending', 2, '2022-06-20', '2022-06-25', 3, '');

--
-- Indexes for dumped tables
--

--
-- Indexes for table `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`voter_id`);

--
-- Indexes for table `voting`
--
ALTER TABLE `voting`
  ADD PRIMARY KEY (`event_id`,`voter_id`);

--
-- Indexes for table `voting_event`
--
ALTER TABLE `voting_event`
  ADD PRIMARY KEY (`event_id`);
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
