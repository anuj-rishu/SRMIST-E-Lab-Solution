import mongoose from "mongoose";
import type { InferSchemaType, Model } from "mongoose";

// Match metadata lives separately: linking an existing solution never rewrites it.
const schema = new mongoose.Schema(
  {
    courseId: { type: Number, required: true },
    questionId: { type: String, required: true },
    fingerprint: { type: String, required: true },
    solutionId: { type: mongoose.Schema.Types.ObjectId, required: true },
    sourceHash: { type: String, required: true },
    samplesPassed: { type: Number, required: true },
    reviewedAt: { type: Date, required: true },
  },
  { collection: "solution_bindings", versionKey: false },
);
schema.index({ courseId: 1, questionId: 1, fingerprint: 1 }, { unique: true });
type BindingDocument = InferSchemaType<typeof schema>;
export const SolutionBinding: Model<BindingDocument> =
  (mongoose.models.SolutionBinding as Model<BindingDocument> | undefined) ||
  mongoose.model<BindingDocument>("SolutionBinding", schema);
