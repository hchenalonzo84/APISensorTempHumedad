/*
  Warnings:

  - You are about to drop the `Sensor` table. If the table is not empty, all the data it contains will be lost.

*/
-- DropTable
DROP TABLE "Sensor";

-- CreateTable
CREATE TABLE "sensor" (
    "id" SERIAL NOT NULL,
    "nombreCompleto" TEXT NOT NULL,
    "correo" TEXT NOT NULL,
    "numCarne" TEXT NOT NULL,
    "latitud" TEXT NOT NULL,
    "longitud" TEXT NOT NULL,
    "humedad" TEXT NOT NULL,
    "temperatura" TEXT NOT NULL,

    CONSTRAINT "sensor_pkey" PRIMARY KEY ("id")
);
