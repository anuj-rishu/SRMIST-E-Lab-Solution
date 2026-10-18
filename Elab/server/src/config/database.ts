import mongoose from "mongoose";

let connecting: Promise<typeof mongoose> | undefined;

export async function connectDatabase(uri: string): Promise<void> {
  if (mongoose.connection.readyState === 1) return;
  if (mongoose.connection.readyState === 0) connecting = undefined;
  if (!connecting) {
    connecting = mongoose.connect(uri, { serverSelectionTimeoutMS: 15000 });
  }
  try {
    await connecting;
  } catch (error) {
    connecting = undefined;
    throw error;
  }
}
