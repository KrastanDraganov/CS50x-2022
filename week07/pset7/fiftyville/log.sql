-- Finding the report about the crime
-- The report is:
-- "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery."
SELECT *
  FROM crime_scene_reports
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND street = "Humphrey Street";


-- Looking for the interviews made at the day of the theft
-- The 3 interviews are:
-- "Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame."
-- "I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money."
-- "As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket."
SELECT *
  FROM interviews
 WHERE year = 2021
   AND month = 7
   AND day = 28;


-- Checking for footage from bakery parking lot in time frame 10:15-10:25
-- Results for the license plates are:
-- 5P2BI95, 94KL13X, 6P58WS2, 4328GD8, G412CB7, L93JTIZ, 322W7JE, 0NTHK55,
SELECT *
  FROM bakery_security_logs
 WHERE year = 2021
   AND month = 7
   AND day = 28
   AND hour = 10
   AND minute >= 15
   AND minute <= 25
   AND activity = "exit";


-- Looking for the earliest flight from Fiftyville tomorrow
-- Information about the earliest flight is:
/*
+----+-------------------+------------------------+------+-------+-----+------+--------+
| id | origin_airport_id | destination_airport_id | year | month | day | hour | minute |
+----+-------------------+------------------------+------+-------+-----+------+--------+
| 36 | 8                 | 4                      | 2021 | 7     | 29  | 8    | 20     |
+----+-------------------+------------------------+------+-------+-----+------+--------+
*/
  SELECT *
    FROM flights
   WHERE year = 2021
     AND month = 7
     AND day = 29
     AND origin_airport_id =
         (SELECT id
            FROM airports
           WHERE city = "Fiftyville")
ORDER BY hour ASC,
         minute ASC
   LIMIT 1;


-- Looking for the destination of the earliest flight as the other information is useless
-- The result is: New York City
SELECT *
  FROM airports
 WHERE id = 4;


-- Looking for information about the passengers of the flight:
SELECT *
  FROM people
 WHERE passport_number IN
       (SELECT passport_number
          FROM passengers
         WHERE flight_id = 36);


-- Looking for matching of the license plates of the cars that left the bakery after the theft iwth the license plates of the passengers
SELECT *
  FROM people
 WHERE passport_number IN
       (SELECT passport_number
          FROM passengers
         WHERE flight_id = 36)
   AND license_plate IN
       (SELECT license_plate
          FROM bakery_security_logs
         WHERE year = 2021
           AND month = 7
           AND day = 28
           AND hour = 10
           AND minute >= 15
           AND minute <= 25
           AND activity = "exit");



-- Looking for people from the flight who made a phone call and have a desired license plate
SELECT pe.name
  FROM phone_calls AS ph,
       people AS pe,
       passengers AS pa,
       bakery_security_logs AS b
 WHERE ph.year = 2021
   AND ph.month = 7
   AND ph.day = 28
   AND ph.duration <= 60
   AND ph.caller = pe.phone_number
   AND pe.passport_number = pa.passport_number
   AND pa.flight_id = 36
   AND pe.license_plate = b.license_plate
   AND b.year = 2021
   AND b.month = 7
   AND b.day = 28
   AND b.hour = 10
   AND b.minute >= 15
   AND b.minute <= 25
   AND b.activity = "exit";


-- Looking for people from the flight who made ATM transactions in the morning on Leggett Street
SELECT pe.name
  FROM atm_transactions AS a,
       bank_accounts AS b,
       people AS pe,
       passengers AS pa
 WHERE a.year = 2021
   AND a.month = 7
   AND a.day = 28
   AND a.atm_location = "Leggett Street"
   AND a.transaction_type = "withdraw"
   AND a.account_number = b.account_number
   AND b.person_id = pe.id
   AND pe.passport_number = pa.passport_number
   AND pa.flight_id = 36;


-- Looking for intersection between people with ATM transactions, Phone Calls and License Plates
-- Result is: Bruce
SELECT pe.name
  FROM phone_calls AS ph,
       people AS pe,
       passengers AS pa,
       bakery_security_logs AS b
 WHERE ph.year = 2021
   AND ph.month = 7
   AND ph.day = 28
   AND ph.duration <= 60
   AND ph.caller = pe.phone_number
   AND pe.passport_number = pa.passport_number
   AND pa.flight_id = 36
   AND pe.license_plate = b.license_plate
   AND b.year = 2021
   AND b.month = 7
   AND b.day = 28
   AND b.hour = 10
   AND b.minute >= 15
   AND b.minute <= 25
   AND b.activity = "exit"


   INTERSECT


SELECT pe.name
  FROM atm_transactions AS a,
       bank_accounts AS b,
       people AS pe,
       passengers AS pa
 WHERE a.year = 2021
   AND a.month = 7
   AND a.day = 28
   AND a.atm_location = "Leggett Street"
   AND a.transaction_type = "withdraw"
   AND a.account_number = b.account_number
   AND b.person_id = pe.id
   AND pe.passport_number = pa.passport_number
   AND pa.flight_id = 36;


-- Looking for the receiver of the call
-- Result: Robin
SELECT name
  FROM people
 WHERE phone_number =
       (SELECT ph.receiver
         FROM people AS pe,
              phone_calls AS ph
        WHERE pe.name = "Bruce"
          AND ph.caller = pe.phone_number
          AND ph.year = 2021
          AND ph.month = 7
          AND ph.day = 28
          AND ph.duration <= 60);