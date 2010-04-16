/*
 *
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 *
 */
package org.apache.qpid.example.jmsexample.hello;

import javax.jms.*;
import javax.naming.Context;
import javax.naming.InitialContext;
import java.util.Properties;


public class Hello {
    private static final String CLASS = "Hello";


    public Hello() {
    }

    public static void main(String[] args) {
        Hello producer = new Hello();
        producer.runTest();
    }

    private void runTest() {
        try {
            Properties properties = new Properties();
            properties.load(this.getClass().getResourceAsStream("hello.properties"));
            Context context = new InitialContext(properties);

            ConnectionFactory connectionFactory = (ConnectionFactory) context.lookup("qpidConnectionfactory");
            Connection connection = connectionFactory.createConnection();
            connection.setExceptionListener(new ExceptionListener() {
                public void onException(JMSException e) {
                    e.printStackTrace();
                }
            });

            Session session = connection.createSession(false, Session.AUTO_ACKNOWLEDGE);
            Destination destination = (Destination) context.lookup("topicExchange");

            MessageProducer messageProducer = session.createProducer(destination);
            MessageConsumer messageConsumer = session.createConsumer(destination);

            Message message = session.createTextMessage("Hello world!");
            messageProducer.send(message);

            message = messageConsumer.receive();
            if (message instanceof TextMessage) {
                String text = ((TextMessage) message).getText();
                System.out.println(text);
            } else {
                System.out.println("Ooops, not a TextMessage!");
            }

            connection.close();
            context.close();
        }
        catch (Exception exp) {
            System.err.println(CLASS + ": Caught an Exception: " + exp);
            exp.printStackTrace();
        }
    }
}
