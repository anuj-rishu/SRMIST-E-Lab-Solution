import mongoose from "mongoose";
import type { InferSchemaType, Model } from "mongoose";

const schema = new mongoose.Schema(
  {
    courseId: { type: Number, required: true },
    Q_ID: { type: String, required: true },
    fingerprint: { type: String, required: true },
    description: { type: String, required: true },
    mandatory: { type: [String], required: true },
    complexity: { type: [Number], required: true },
    testcases: { type: [mongoose.Schema.Types.Mixed], required: true },
    solutionId: mongoose.Schema.Types.ObjectId,
    sourceHash: String,
    evidence: String,
    discoveredAccount: { type: Number, required: true },
    firstSequence: { type: Number, required: true },
    embedding: { type: [Number], select: false },
    embeddingText: String,
    embeddingModel: String,
    embeddingRevision: String,
    embeddingVersion: String,
    embeddingHash: String,
    createdAt: { type: Date, required: true },
  },
  { collection: "question_catalog", versionKey: false },
);
schema.index({ courseId: 1, Q_ID: 1 }, { unique: true });
type QuestionDocument = InferSchemaType<typeof schema>;
export const QuestionCatalog: Model<QuestionDocument> =
  (mongoose.models.QuestionCatalog as Model<QuestionDocument> | undefined) ||
  mongoose.model<QuestionDocument>("QuestionCatalog", schema);
