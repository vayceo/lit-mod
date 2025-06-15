-- phpMyAdmin SQL Dump
-- version 4.9.7
-- https://www.phpmyadmin.net/
--
-- Хост: 127.0.0.1:3306
-- Время создания: Ноя 18 2024 г., 22:07
-- Версия сервера: 11.3.2-MariaDB
-- Версия PHP: 7.4.33

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET AUTOCOMMIT = 0;
START TRANSACTION;
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- База данных: `gs89935`
--

-- --------------------------------------------------------

--
-- Структура таблицы `action_log`
--

CREATE TABLE `action_log` (
  `id` int(11) NOT NULL,
  `acc_id` int(11) NOT NULL,
  `type` int(11) NOT NULL,
  `description` varchar(128) NOT NULL,
  `time` int(11) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `action_log`
--

INSERT INTO `action_log` (`id`, `acc_id`, `type`, `description`, `time`) VALUES
(876, 56, 3, 'Телепортировался к Maks_Kotov[acc:7852]', 1730496636);

-- --------------------------------------------------------

--
-- Структура таблицы `admin_stats`
--

CREATE TABLE `admin_stats` (
  `admin_id` int(11) NOT NULL,
  `bans` int(11) DEFAULT 0,
  `mutes` int(11) DEFAULT 0,
  `unbans` int(11) DEFAULT 0,
  `kicks` int(11) DEFAULT 0,
  `warns` int(11) DEFAULT 0
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `admin_stats`
--

INSERT INTO `admin_stats` (`admin_id`, `bans`, `mutes`, `unbans`, `kicks`, `warns`) VALUES
(56, 3, 1, 0, 1, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `ban_list`
--

CREATE TABLE `ban_list` (
  `id` int(11) NOT NULL,
  `user_id` int(11) NOT NULL,
  `time` int(11) NOT NULL,
  `ban_time` int(11) NOT NULL,
  `description` varchar(32) NOT NULL,
  `admin` varchar(24) NOT NULL
) ENGINE=MyISAM DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `ban_list`
--

INSERT INTO `ban_list` (`id`, `user_id`, `time`, `ban_time`, `description`, `admin`) VALUES
(1, 1515, 1730246400, 1732838400, 'test', 'Tayk_Boss');

-- --------------------------------------------------------

--
-- Структура таблицы `console_users`
--

CREATE TABLE `console_users` (
  `id` int(11) NOT NULL,
  `username` varchar(50) NOT NULL,
  `password` varchar(255) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;

--
-- Дамп данных таблицы `console_users`
--

INSERT INTO `console_users` (`id`, `username`, `password`) VALUES
(7, 'tayk14', '$2y$10$OoLCD6emhqtDOmhBYxzsjuawj6oUqEkj1HPVgtvVgfokUDEUeWS4m');

-- --------------------------------------------------------

--
-- Структура таблицы `users`
--

CREATE TABLE `users` (
  `ID` int(11) NOT NULL,
  `Name` varchar(24) NOT NULL,
  `Pass` varchar(32) NOT NULL,
  `Email` varchar(46) NOT NULL,
  `Referal` varchar(24) NOT NULL,
  `Date Reg` varchar(10) NOT NULL,
  `Skin` int(3) NOT NULL,
  `Money` int(11) NOT NULL,
  `Level` int(4) NOT NULL,
  `Admin` int(1) NOT NULL,
  `Mute` int(3) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `users`
--

INSERT INTO `users` (`ID`, `Name`, `Pass`, `Email`, `Referal`, `Date Reg`, `Skin`, `Money`, `Level`, `Admin`, `Mute`) VALUES
(56, 'Tayk_Boss', 'password', 'test@gmail.com', '', '27/10/2024', 7, 14449444, 1, 5, 0);

-- --------------------------------------------------------

--
-- Структура таблицы `whitelist`
--

CREATE TABLE `whitelist` (
  `id` int(11) NOT NULL,
  `name` varchar(50) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb3 COLLATE=utf8mb3_general_ci;

--
-- Дамп данных таблицы `whitelist`
--

INSERT INTO `whitelist` (`id`, `name`) VALUES
(2, 'Tayk_Boss');

--
-- Индексы сохранённых таблиц
--

--
-- Индексы таблицы `action_log`
--
ALTER TABLE `action_log`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `admin_stats`
--
ALTER TABLE `admin_stats`
  ADD PRIMARY KEY (`admin_id`);

--
-- Индексы таблицы `ban_list`
--
ALTER TABLE `ban_list`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `console_users`
--
ALTER TABLE `console_users`
  ADD PRIMARY KEY (`id`);

--
-- Индексы таблицы `users`
--
ALTER TABLE `users`
  ADD PRIMARY KEY (`ID`);

--
-- Индексы таблицы `whitelist`
--
ALTER TABLE `whitelist`
  ADD PRIMARY KEY (`id`),
  ADD UNIQUE KEY `name` (`name`);

--
-- AUTO_INCREMENT для сохранённых таблиц
--

--
-- AUTO_INCREMENT для таблицы `action_log`
--
ALTER TABLE `action_log`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=26688;

--
-- AUTO_INCREMENT для таблицы `ban_list`
--
ALTER TABLE `ban_list`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=635;

--
-- AUTO_INCREMENT для таблицы `console_users`
--
ALTER TABLE `console_users`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=9;

--
-- AUTO_INCREMENT для таблицы `users`
--
ALTER TABLE `users`
  MODIFY `ID` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=30853;

--
-- AUTO_INCREMENT для таблицы `whitelist`
--
ALTER TABLE `whitelist`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=6;
COMMIT;

/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
