import java.io.Serializable;
import java.util.Enumeration;

public class Prism {

  /**
   * Class for storing a PRISM ruleset, i.e. a list of rules
   */
  private class PrismRule
    implements Serializable{

    /** The classification */
    private int m_classification;

    /** The instance */
    private Instances m_instances;

    /** First test of this rule */
    private Test m_test;

    /** The next rule in the list */
    private PrismRule m_next;
    public PrismRule(Instances data, int cl) throws Exception {

      m_instances = data;
      m_classification = cl;
      m_test = null;
      m_next = null;
      m_errors = 0;
      Enumeration enu = data.enumerateInstances();
      while (enu.hasMoreElements()) {
        if ((int) ((Instance) enu.nextElement()).classValue() != cl) {
	  m_errors++;
	}
      }
      m_instances = new Instances(m_instances, 0);
    }

    /**
     * Returns the result assigned by this rule to a given instance.
     *
     * @param inst the instance to be classified
     * @return the classification
     */
    public int resultRule(Instance inst) {

      if (m_test == null || m_test.satisfies(inst)) {
	return m_classification;
      } else {
	return -1;
      }
    }

    /**
     * Returns the result assigned by these rules to a given instance.
     *
     * @param inst the instance to be classified
     * @return the classification
     */
    public int resultRules(Instance inst) {

      if (resultRule(inst) != -1) {
	return m_classification;
      } else if (m_next != null) {
	return m_next.resultRules(inst);
      } else {
	return -1;
      }
    }

    /**
     * Returns the set of instances that are covered by this rule.
     *
     * @param data the instances to be checked
     * @return the instances covered
     */
    public Instances coveredBy(Instances data) {

      Instances r = new Instances(data, data.numInstances());
      Enumeration enu = data.enumerateInstances();
      while (enu.hasMoreElements()) {
	Instance i = (Instance) enu.nextElement();
	if (resultRule(i) != -1) {
	  r.add(i);
	}
      }
      r.compactify();
      return r;
    }

    /**
     * Returns the set of instances that are not covered by this rule.
     *
     * @param data the instances to be checked
     * @return the instances not covered
     */
    public Instances notCoveredBy(Instances data) {

      Instances r = new Instances(data, data.numInstances());
      Enumeration enu = data.enumerateInstances();
      while (enu.hasMoreElements()) {
	Instance i = (Instance) enu.nextElement();
	if (resultRule(i) == -1) {
	  r.add(i);
	}
      }
      r.compactify();
      return r;
    }

    /**
     * Prints the set of rules.
     *
     * @return a description of the rules as a string
     */
    public String toString() {

      try {
	StringBuffer text = new StringBuffer();
	if (m_test != null) {
	  text.append("If ");
	  for (Test t = m_test; t != null; t = t.m_next) {
	    if (t.m_attr == -1) {
	      text.append("?");
	    } else {
	      text.append(m_instances.attribute(t.m_attr).name() + " = " +
			  m_instances.attribute(t.m_attr).value(t.m_val));
	    }
	    if (t.m_next != null) {
	      text.append("\n   and ");
	    }
	  }
	  text.append(" then ");
	}
	text.append(m_instances.classAttribute().value(m_classification) + "\n");
	if (m_next != null) {
	  text.append(m_next.toString());
	}
	return text.toString();
      } catch (Exception e) {
	return "Can't print Prism classifier!";
      }
    }

    /**
     * Returns the revision string.
     *
     * @return		the revision
     */
    public String getRevision() {
      return RevisionUtils.extract("$Revision: 5987 $");
    }
  }

  /**
   * Class for storing a list of attribute-value tests
   */
  private class Test
    implements Serializable, RevisionHandler {

    /** for serialization */
    static final long serialVersionUID = -8925333011350280799L;

    /** Attribute to test */
    private int m_attr = -1;

    /** The attribute's value */
    private int m_val;

    /** The next test in the rule */
    private Test m_next = null;

    /**
     * Returns whether a given instance satisfies this test.
     *
     * @param inst the instance to be tested
     * @return true if the instance satisfies the test
     */
    private boolean satisfies(Instance inst) {

      if ((int) inst.value(m_attr) == m_val) {
        if (m_next == null) {
	  return true;
	} else {
	  return m_next.satisfies(inst);
	}
      }
      return false;
    }

    /**
     * Returns the revision string.
     *
     * @return		the revision
     */
    public String getRevision() {
      return RevisionUtils.extract("$Revision: 5987 $");
    }
  }

  /** The first rule in the list of rules */
  private PrismRule m_rules;

  /**
   * Classifies a given instance.
   *
   * @param inst the instance to be classified
   * @return the classification
   */
  public double classifyInstance(Instance inst) {

    int result = m_rules.resultRules(inst);
    if (result == -1) {
      return Utils.missingValue();
    } else {
      return (double)result;
    }
  }

  /**
   * Returns default capabilities of the classifier.
   *
   * @return      the capabilities of this classifier
   */
  public Capabilities getCapabilities() {
    Capabilities result = super.getCapabilities();
    result.disableAll();

    // attributes
    result.enable(Capability.NOMINAL_ATTRIBUTES);

    // class
    result.enable(Capability.NOMINAL_CLASS);
    result.enable(Capability.MISSING_CLASS_VALUES);

    return result;
  }

  /**
   * Generates the classifier.
   *
   * @param data the data to be used
   * @exception Exception if the classifier can't built successfully
   */
  public void buildClassifier(Instances data) throws Exception {

    int cl; // possible value of theClass
    Instances E, ruleE;
    PrismRule rule = null;
    Test test = null, oldTest = null;
    int bestCorrect, bestCovers, attUsed;
    Enumeration enumAtt;

    // can classifier handle the data?
    getCapabilities().testWithFail(data);

    // remove instances with missing class
    data = new Instances(data);
    data.deleteWithMissingClass();

    for (cl = 0; cl < data.numClasses(); cl++) { // for each class cl
      E = data; // initialize E to the instance set
      while (contains(E, cl)) { // while E contains examples in class cl
        rule = addRule(rule, new PrismRule(E, cl)); // make a new rule
        ruleE = E; // examples covered by this rule
        while (rule.m_errors != 0) { // until the rule is perfect
          test = new Test(); // make a new test
          bestCorrect = bestCovers = attUsed = 0;

          // for every attribute not mentioned in the rule
          enumAtt = ruleE.enumerateAttributes();
          while (enumAtt.hasMoreElements()) {
            Attribute attr = (Attribute) enumAtt.nextElement();
            if (isMentionedIn(attr, rule.m_test)) {
	      attUsed++;
	      continue;
	    }
            int M = attr.numValues();
            int[] covers = new int [M];
            int[] correct = new int [M];
            for (int j = 0; j < M; j++) {
	      covers[j] = correct[j] = 0;
	    }

            // ... calculate the counts for this class
            Enumeration enu = ruleE.enumerateInstances();
            while (enu.hasMoreElements()) {
              Instance i = (Instance) enu.nextElement();
              covers[(int) i.value(attr)]++;
              if ((int) i.classValue() == cl) {
                correct[(int) i.value(attr)]++;
	      }
            }

            // ... for each value of this attribute, see if this test is better
            for (int val = 0; val < M; val ++) {
              int diff = correct[val] * bestCovers - bestCorrect * covers[val];

              // this is a ratio test, correct/covers vs best correct/covers
              if (test.m_attr == -1
                  || diff > 0 || (diff == 0 && correct[val] > bestCorrect)) {

                // update the rule to use this test
                bestCorrect = correct[val];
                bestCovers = covers[val];
                test.m_attr = attr.index();
                test.m_val = val;
                rule.m_errors = bestCovers - bestCorrect;
              }
            }
          }
	  if (test.m_attr == -1) { // Couldn't find any sensible test
	    break;
	  }
	  oldTest = addTest(rule, oldTest, test);
	  ruleE = rule.coveredBy(ruleE);
	  if (attUsed == (data.numAttributes() - 1)) { // Used all attributes.
	    break;
	  }
        }
        E = rule.notCoveredBy(E);
      }
    }
  }

  /**
   * Add a rule to the ruleset.
   *
   * @param lastRule the last rule in the rule set
   * @param newRule the rule to be added
   * @return the new last rule in the rule set
   */
  private PrismRule addRule(PrismRule lastRule, PrismRule newRule) {

    if (lastRule == null) {
      m_rules = newRule;
    } else {
      lastRule.m_next = newRule;
    }
    return newRule;
  }

  /**
   * Add a test to this rule.
   *
   * @param rule the rule to which test is to be added
   * @param lastTest the rule's last test
   * @param newTest the test to be added
   * @return the new last test of the rule
   */
  private Test addTest(PrismRule rule, Test lastTest, Test newTest) {

    if (rule.m_test == null) {
      rule.m_test = newTest;
    } else {
      lastTest.m_next = newTest;
    }
    return newTest;
  }

  /**
   * Does E contain any examples in the class C?
   *
   * @param E the instances to be checked
   * @param C the class
   * @return true if there are any instances of class C
   * @throws Exception if something goes wrong
   */
  private static boolean contains(Instances E, int C) throws Exception {

    Enumeration enu = E.enumerateInstances();
    while (enu.hasMoreElements()) {
      if ((int) ((Instance) enu.nextElement()).classValue() == C) {
	return true;
      }
    }
    return false;
  }

  /**
   * Is this attribute mentioned in the rule?
   *
   * @param attr the attribute to be checked for
   * @param t test contained by rule
   * @return true if the attribute is mentioned in the rule
   */
  private static boolean isMentionedIn(Attribute attr, Test t) {

    if (t == null) {
      return false;
    }
    if (t.m_attr == attr.index()) {
      return true;
    }
    return isMentionedIn(attr, t.m_next);
  }

  /**
   * Prints a description of the classifier.
   *
   * @return a description of the classifier as a string
   */
  public String toString() {

    if (m_rules == null) {
      return "Prism: No model built yet.";
    }
    return "Prism rules\n----------\n" + m_rules.toString();
  }

  /**
   * Returns the revision string.
   *
   * @return		the revision
   */
  public String getRevision() {
    return RevisionUtils.extract("$Revision: 5987 $");
  }

  /**
   * Main method for testing this class
   *
   * @param args the commandline parameters
   */
  public static void main(String[] args) {
    runClassifier(new Prism(), args);
  }
}
