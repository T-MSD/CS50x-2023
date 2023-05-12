-- Keep a log of any SQL queries you execute as you solve the mystery.

SELECT * FROM crime_scene_reports
WHERE year = 2021 AND day = 28 AND month = 7 AND street = 'Humphrey Street';
-- theft took place at 10:15 at humphrey bakery, 3 interviews refered the bakery

SELECT * FROM interviews
WHERE year = 2021 AND day = 28 AND month = 7;
-- Ruth: saw the thief get into a car at the bakery parking lot, within a 10 min window (look for cars that left in that window)
-- Eugene: Recognized th thief. Earlier he saw him withdrawing some money at the ATM on Leggett Street
-- Raymond: Saw the thief calling someone (less than 1 min call) they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.

SELECT * FROM bakery_security_logs
WHERE year = 2021 AND month = 7 AND day = 28 AND hour = 10 AND minute BETWEEN 15 AND 25;
-- 260|2021|7|28|10|16|exit|5P2BI95
-- 261|2021|7|28|10|18|exit|94KL13X
-- 262|2021|7|28|10|18|exit|6P58WS2
-- 263|2021|7|28|10|19|exit|4328GD8
-- 264|2021|7|28|10|20|exit|G412CB7
-- 265|2021|7|28|10|21|exit|L93JTIZ
-- 266|2021|7|28|10|23|exit|322W7JE
-- 267|2021|7|28|10|23|exit|0NTHK55

SELECT * FROM atm_transactions
WHERE year = 2021 AND day = 28 AND month = 7 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
-- 246|28500762|2021|7|28|Leggett Street|withdraw|48
-- 264|28296815|2021|7|28|Leggett Street|withdraw|20
-- 266|76054385|2021|7|28|Leggett Street|withdraw|60
-- 267|49610011|2021|7|28|Leggett Street|withdraw|50
-- 269|16153065|2021|7|28|Leggett Street|withdraw|80
-- 288|25506511|2021|7|28|Leggett Street|withdraw|20
-- 313|81061156|2021|7|28|Leggett Street|withdraw|30
-- 336|26013199|2021|7|28|Leggett Street|withdraw|35

SELECT name FROM people
JOIN phone_calls ON phone_calls.caller = people.phone_number
WHERE phone_calls.year = 2021 AND phone_calls.day = 28 AND phone_calls.month = 7 AND phone_calls.duration < 60;
-- Sofia, Kelsey, Bruce, Kelsey, Taylor, Diana, Carina, Kenny, Benista

SELECT name FROM people WHERE id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2021 AND day = 28 AND month = 7 AND transaction_type = 'withdraw' AND atm_location = 'Leggett Street'))
AND people.phone_number IN (SELECT caller FROM phone_calls WHERE year = 2021 AND day = 28 AND month = 7 AND duration < 60)
AND people.passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE year = 2021 AND day = 29 AND month = 7 AND origin_airport_id IN (SELECT id FROM airports WHERE city = 'Fiftyville') ORDER BY hour LIMIT 1))
AND people.license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2021 AND day = 28 AND month = 7 AND hour = 10 AND minute BETWEEN 15 AND 25 AND activity = 'exit');
-- Bruce

SELECT name FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE caller IN (SELECT phone_number FROM people WHERE name = 'Bruce') AND year = 2021 AND month = 7 AND day = 28 AND duration < 60);
-- Robin

SELECT city FROM airports WHERE id IN (SELECT destination_airport_id FROM flights WHERE year = 2021 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1);
-- New York City