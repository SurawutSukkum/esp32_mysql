-- phpMyAdmin SQL Dump
-- version 4.9.7
-- https://www.phpmyadmin.net/
--
-- Host: localhost
-- Generation Time: May 17, 2025 at 12:35 PM
-- Server version: 10.6.17-MariaDB
-- PHP Version: 5.6.40

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";

CREATE TABLE `mesh_dataV1` (
  `No` int(11) NOT NULL,
  `TimeStamp` timestamp NOT NULL DEFAULT current_timestamp(),
  `Node` text DEFAULT NULL,
  `Temp` varchar(6) DEFAULT NULL,
  `Humi` varchar(6) DEFAULT NULL,
  `Pressure` varchar(6) DEFAULT NULL,
  `Led` text DEFAULT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
