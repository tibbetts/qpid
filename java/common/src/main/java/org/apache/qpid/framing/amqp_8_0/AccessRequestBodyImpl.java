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

/*
 * This file is auto-generated by Qpid Gentools v.0.1 - do not modify.
 * Supported AMQP version:
 *   8-0
 */

package org.apache.qpid.framing.amqp_8_0;

import org.apache.qpid.codec.MarkableDataInput;
import java.io.DataOutput;
import java.io.IOException;

import org.apache.qpid.framing.*;
import org.apache.qpid.AMQException;

public class AccessRequestBodyImpl extends AMQMethodBody_8_0 implements AccessRequestBody
{
    private static final AMQMethodBodyInstanceFactory FACTORY_INSTANCE = new AMQMethodBodyInstanceFactory()
    {
        public AMQMethodBody newInstance(MarkableDataInput in, long size) throws AMQFrameDecodingException, IOException
        {
            return new AccessRequestBodyImpl(in);
        }
    };

    public static AMQMethodBodyInstanceFactory getFactory()
    {
        return FACTORY_INSTANCE;
    }

    public static final int CLASS_ID =  30;
    public static final int METHOD_ID = 10;

    // Fields declared in specification
    private final AMQShortString _realm; // [realm]
    private final byte _bitfield0; // [exclusive, passive, active, write, read]

    // Constructor
    public AccessRequestBodyImpl(MarkableDataInput buffer) throws AMQFrameDecodingException, IOException
    {
        _realm = readAMQShortString( buffer );
        _bitfield0 = readBitfield( buffer );
    }

    public AccessRequestBodyImpl(
                                AMQShortString realm,
                                boolean exclusive,
                                boolean passive,
                                boolean active,
                                boolean write,
                                boolean read
                            )
    {
        _realm = realm;
        byte bitfield0 = (byte)0;
        if( exclusive )
        {
            bitfield0 = (byte) (((int) bitfield0) | (1 << 0));
        }

        if( passive )
        {
            bitfield0 = (byte) (((int) bitfield0) | (1 << 1));
        }

        if( active )
        {
            bitfield0 = (byte) (((int) bitfield0) | (1 << 2));
        }

        if( write )
        {
            bitfield0 = (byte) (((int) bitfield0) | (1 << 3));
        }

        if( read )
        {
            bitfield0 = (byte) (((int) bitfield0) | (1 << 4));
        }
        _bitfield0 = bitfield0;
    }

    public int getClazz()
    {
        return CLASS_ID;
    }

    public int getMethod()
    {
        return METHOD_ID;
    }

    public final AMQShortString getRealm()
    {
        return _realm;
    }
    public final boolean getExclusive()
    {
        return (((int)(_bitfield0)) & ( 1 << 0)) != 0;
    }
    public final boolean getPassive()
    {
        return (((int)(_bitfield0)) & ( 1 << 1)) != 0;
    }
    public final boolean getActive()
    {
        return (((int)(_bitfield0)) & ( 1 << 2)) != 0;
    }
    public final boolean getWrite()
    {
        return (((int)(_bitfield0)) & ( 1 << 3)) != 0;
    }
    public final boolean getRead()
    {
        return (((int)(_bitfield0)) & ( 1 << 4)) != 0;
    }

    protected int getBodySize()
    {
        int size = 1;
        size += getSizeOf( _realm );
        return size;
    }

    public void writeMethodPayload(DataOutput buffer) throws IOException
    {
        writeAMQShortString( buffer, _realm );
        writeBitfield( buffer, _bitfield0 );
    }

    public boolean execute(MethodDispatcher dispatcher, int channelId) throws AMQException
	{
    return ((MethodDispatcher_8_0)dispatcher).dispatchAccessRequest(this, channelId);
	}

    public String toString()
    {
        StringBuilder buf = new StringBuilder("[AccessRequestBodyImpl: ");
        buf.append( "realm=" );
        buf.append(  getRealm() );
        buf.append( ", " );
        buf.append( "exclusive=" );
        buf.append(  getExclusive() );
        buf.append( ", " );
        buf.append( "passive=" );
        buf.append(  getPassive() );
        buf.append( ", " );
        buf.append( "active=" );
        buf.append(  getActive() );
        buf.append( ", " );
        buf.append( "write=" );
        buf.append(  getWrite() );
        buf.append( ", " );
        buf.append( "read=" );
        buf.append(  getRead() );
        buf.append("]");
        return buf.toString();
    }

}