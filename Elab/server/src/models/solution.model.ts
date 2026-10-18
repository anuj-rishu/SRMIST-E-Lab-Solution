import mongoose from "mongoose";
import type { InferSchemaType, Model } from "mongoose";

export const COURSE_IDS = { c: 11, dsa: 26 } as const;

const solutionSchema = new mongoose.Schema(
  {
    filename: { type: String, required: true },
    title: { type: String, required: true },
    category: { type: String, required: true, enum: ["c", "dsa"] },
    categoryLabel: { type: String, required: true },
    tags: { type: [String], required: true, default: undefined },
    solution: { type: String, required: true },
    verifiedQuestionId: String,
    verifiedFingerprint: String,
    verifiedPercentage: Number,
    embedding: { type: [Number], default: undefined, select: false },
    embeddingText: String,
    embeddingModel: String,
    embeddingRevision: String,
    embeddingVersion: String,
    embeddingHash: String,
    embeddingUpdatedAt: Date,
    courseId: {
      type: Number,
      required: true,
      enum: Object.values(COURSE_IDS),
      default: function (this: { category: keyof typeof COURSE_IDS }): number {
        return COURSE_IDS[this.category];
      },
    },
  },
  { collection: "solutions", strict: "throw", versionKey: false },
);

solutionSchema.index({ category: 1, filename: 1 }, { unique: true });

type SolutionDocument = InferSchemaType<typeof solutionSchema>;

export const Solution: Model<SolutionDocument> =
  (mongoose.models.Solution as Model<SolutionDocument> | undefined) ||
  mongoose.model<SolutionDocument>("Solution", solutionSchema);
